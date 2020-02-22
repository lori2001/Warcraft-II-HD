#include "EditableMap.h"
#include "../Common/GameDetails.h"
#include "nfd.h"

EditableMap::EditableMap()
{
	selectedTile_.setFillColor(sf::Color(255,255,0,80));
	mouseHeld_ = false;

	logs_.clear();
	lastChange_ = -1; // -1 means no changes
}

bool EditableMap::setMapFile()
{
	nfdchar_t* outPath = NULL;
	nfdresult_t result = NFD_OpenDialog("mapfile", GameDetails::mapFile.getFolderPath().c_str(), &outPath);

	if (result == NFD_OKAY) {
		GameDetails::mapFile.read(outPath);
		NG_LOG_INFO(GameDetails::mapFile.getMapName());
	}
	else if (result == NFD_ERROR) {
		NG_LOG_ERROR("Error: %s\n", NFD_GetError());
		return false;
	}
	else {
		return false;
	}

	Map::setMapFile(GameDetails::mapFile);
	return true;
}

void EditableMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	Map::draw(target, states);

	if (drawSelected_) {
		target.draw(selectedTile_);
	}

	if (gridIsActive_) {
		for (int i = 0; i < int(gridLines_.size()); i++) {
			sf::Vertex line[] = {
				gridLines_[i].point1,
				gridLines_[i].point2
			};
			target.draw(line, 2, sf::Lines);
		}
	}
}

void EditableMap::updateGrid()
{
	// --- Grid Calculations --------------------------------------
	topLeft_ = {
		getPosition().x - getScaledSize().x / 2, getPosition().y - getScaledSize().y / 2 };
	bottomRight_ = {
		getPosition().x + getScaledSize().x / 2, getPosition().y + getScaledSize().y / 2 };

	lineDistance_ = {
		Map::getTileSize().x * Map::getScale().x,
		Map::getTileSize().y * Map::getScale().y };

	numOfTiles_ = ngin::divVec(topLeft_, lineDistance_);

	// distance from the start of the screen
	distFromStart_ = { topLeft_.x - lineDistance_.x * static_cast<int>(numOfTiles_.x),
	   			      topLeft_.y - lineDistance_.y * static_cast<int>(numOfTiles_.y) };

	if (gridIsActive_) {
		// deletes old grid lines before recalculating them
		gridLines_.clear();

		for (float x = distFromStart_.x; x <= ngin::MainLevel::view_.getSize().x; x += lineDistance_.x) {
			Line XLine{
				sf::Vertex(sf::Vector2f(x, 0)),
				sf::Vertex(sf::Vector2f(x, ngin::MainLevel::view_.getSize().y))
			};

			gridLines_.push_back(XLine);
		}
		for (float y = distFromStart_.y; y <= ngin::MainLevel::view_.getSize().y; y += lineDistance_.y) {
			Line YLine{
				sf::Vertex(sf::Vector2f(0, y)),
				sf::Vertex(sf::Vector2f(ngin::MainLevel::view_.getSize().x, y))
			};

			gridLines_.push_back(YLine);
		}
	}

	adjustSelectedTile();
	// ------------------------------------------------------------
}

void EditableMap::handleEvents(const sf::Event& event, const TilePainter& tilePainter)
{
	// cntrl+shift+z = redo
	if (event.type == sf::Event::KeyPressed &&
		sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) &&
		sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) &&
		event.key.code == sf::Keyboard::Z)
	{
		redoChange();
	}
	// cntrl+z = undo
	else if (event.type == sf::Event::KeyPressed &&
		sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) &&
		event.key.code == sf::Keyboard::Z)
	{
		undoChange();
	}

	// stop placing tiles
	if (event.mouseButton.button == sf::Mouse::Left &&
		event.type == sf::Event::MouseButtonReleased) {
		mouseHeld_ = false;
	}

	if (isFocused_) {
		sf::Vector2i lastCoords = selectedTileCoords_;
		adjustSelectedTile();

		// start placing tiles
		if (event.mouseButton.button == sf::Mouse::Left &&
			event.type == sf::Event::MouseButtonPressed) {
			mouseHeld_ = true;
		}

		// place tiles
		if (((mouseHeld_ && lastCoords != selectedTileCoords_) || // on hold
			 (event.mouseButton.button == sf::Mouse::Left // or on click
			  && event.type == sf::Event::MouseButtonPressed))
			&& !ngin::UIElement::hasBlockingException()) // AND no dropped-downs
		{
			if (tilePainter.usingTile() != -1) {

				// delete invalid changes in the log
				if (lastChange_ == -1) {
					// bugfix for a strange situation
					logs_.clear();
				}
				else if (lastChange_ < static_cast<int>(logs_.size()) - 1)
				{
					// delete the interval (lastChange_, end)
					logs_.erase(logs_.begin() + lastChange_ + 1, logs_.end());
				}
				
				// if in bounds
				if (selectedTileCoords_.y >= 0 &&
					selectedTileCoords_.y < GameDetails::mapFile.getNRows() &&
					selectedTileCoords_.x >= 0 &&
					selectedTileCoords_.x < GameDetails::mapFile.getNColumns(selectedTileCoords_.y))
				{
					// add state before change to logs' stack
					logs_.push_back({
						selectedTileCoords_.x,
						selectedTileCoords_.y,
						static_cast<int>(
							GameDetails::mapFile.getTileNum(selectedTileCoords_.y, selectedTileCoords_.x)
						)
						});
					
					lastChange_ = logs_.size() - 1;
				}
				else { // if not in bounds log an empty square there
					logs_.push_back({ selectedTileCoords_.x, selectedTileCoords_.y, 0 });
					lastChange_ = logs_.size() - 1;
				}

				// add new tile to file
				GameDetails::mapFile.addNewTile(tilePainter.usingTile(), selectedTileCoords_);
				Map::setMapFile(GameDetails::mapFile); // reread file
			}
		}
		// ------------------------------------------------------------
	}
	else {
		drawSelected_ = false;
	}

}

void EditableMap::setScale(const sf::Vector2f& scale)
{
	Map::setScale(scale);
	updateGrid();
}

void EditableMap::setPosition(const sf::Vector2f& position)
{
	Map::setPosition(position);
}

void EditableMap::setOrigin(const sf::Vector2f& origin)
{
	Map::setOrigin(origin);
}

void EditableMap::adjustSelectedTile()
{
	if (isFocused_) {
		// --- Selected Tile ------------------------------------------
		// Number of tiles behind cursor
		sf::Vector2f tilesBehind =
			ngin::divVec(ngin::subsVec(ngin::Cursor::getPosition(), distFromStart_), lineDistance_);;

		// exact position of the highlight
		sf::Vector2f selectedPosition = { distFromStart_.x + lineDistance_.x * static_cast<int>(tilesBehind.x),
										  distFromStart_.y + lineDistance_.y * static_cast<int>(tilesBehind.y) };

		// constrain slected tile position on the edge+-1 of the matrix of tiles
		if (ngin::Cursor::getPosition().x <= topLeft_.x - getScaledTileSize().x) {
			selectedPosition.x = topLeft_.x - getScaledTileSize().x;
		}
		if (ngin::Cursor::getPosition().y <= topLeft_.y - getScaledTileSize().y) {
			selectedPosition.y = topLeft_.y - getScaledTileSize().y;
		}
		if (ngin::Cursor::getPosition().x >= bottomRight_.x) {
			selectedPosition.x = bottomRight_.x;
		}
		if (ngin::Cursor::getPosition().y >= bottomRight_.y) {
			selectedPosition.y = bottomRight_.y;
		}

		// calculate position inside mapfile matrix
		selectedTileCoords_.x =
			static_cast<unsigned>(std::round(std::round(selectedPosition.x - topLeft_.x) / getScaledTileSize().x));
		selectedTileCoords_.y =
			static_cast<unsigned>(std::round(std::round(selectedPosition.y - topLeft_.y) / getScaledTileSize().y));

		drawSelected_ = true;
		selectedTile_.setSize(lineDistance_);
		selectedTile_.setPosition(selectedPosition);
	}
}

void EditableMap::undoChange()
{
	// if there are changes to undo
	if (lastChange_ >= 0)
	{
		// save the value of the tile (for redo to work)
		int savedVal = GameDetails::mapFile.getTileNum( logs_[lastChange_].y, logs_[lastChange_].x );

		// undo the last change made change
		GameDetails::mapFile.addNewTile(
			logs_[lastChange_].z,
			{ logs_[lastChange_].x, logs_[lastChange_].y });

		// apply changes
		logs_[lastChange_].z = savedVal;
		Map::setMapFile(GameDetails::mapFile);

		// move lastChange down by 1 in vector
		lastChange_--;
	}
	else {
		NG_LOG_NOTE("There are no more changes to be undone!");
	}
}

void EditableMap::redoChange()
{
	int changeBefore = lastChange_ + 1; // change numerically after last

	// if there are changes to be redone
	if (static_cast<int>(logs_.size()) > changeBefore) 
	{
		// save the value of the tile (for undo to work)
		int savedVal = GameDetails::mapFile.getTileNum(logs_[changeBefore].y, logs_[changeBefore].x);

		// redo changes
		GameDetails::mapFile.addNewTile(
			logs_[changeBefore].z,
			{ logs_[changeBefore].x, logs_[changeBefore].y });

		// apply changes
		logs_[changeBefore].z = savedVal;
		Map::setMapFile(GameDetails::mapFile);

		// move lastChange up by 1 in vector
		lastChange_++;
	}
	else {
		NG_LOG_NOTE("There are no more changes to be redone!");
	}
}

void EditableMap::move(const sf::Vector2f& offset)
{
	Map::move(offset);
	updateGrid();
}
