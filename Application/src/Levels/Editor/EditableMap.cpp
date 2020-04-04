#include "EditableMap.h"
#include "nfd.h"

EditableMap::EditableMap()
{
	selectedTile_.setFillColor(sf::Color(255,255,0,80));
}

bool EditableMap::setMapFile(const MapFile& mapFile)
{
	nfdchar_t* outPath = NULL;
	nfdresult_t result = NFD_OpenDialog("mapfile", GameDetails::mapFile.getFolderPath().c_str(), &outPath);

	if (result == NFD_OKAY) {
		GameDetails::mapFile.load(outPath);
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

	numOfTiles_ = ng::divVec(topLeft_, lineDistance_);

	distFromStart_ = { topLeft_.x - lineDistance_.x * static_cast<int>(numOfTiles_.x),
	   			      topLeft_.y - lineDistance_.y * static_cast<int>(numOfTiles_.y) };

	if (gridIsActive_) {
		// deletes old grid lines before recalculating them
		gridLines_.clear();

		for (float x = distFromStart_.x; x <= ng::Main::view.getSize().x; x += lineDistance_.x) {
			Line XLine{
				sf::Vertex(sf::Vector2f{x, 0}),
				sf::Vertex(sf::Vector2f{x, ng::Main::view.getSize().y})
			};

			gridLines_.push_back(XLine);
		}
		for (float y = distFromStart_.y; y <= ng::Main::view.getSize().y; y += lineDistance_.y) {
			Line YLine{
				sf::Vertex(sf::Vector2f{0, y}),
				sf::Vertex(sf::Vector2f{ng::Main::view.getSize().x, y})
			};

			gridLines_.push_back(YLine);
		}
	}

	adjustSelectedTile();
	// ------------------------------------------------------------
}

void EditableMap::handleEvents(const sf::Event& event, const TilePainter& tilePainter)
{
	if (isFocused_) {
		adjustSelectedTile();

		// place tile
		if (event.mouseButton.button == sf::Mouse::Left &&
			event.type == sf::Event::MouseButtonPressed &&
			!ng::UIElement::hasBlockingException()) // no dropped-downs
		{
			NG_LOG_ERROR(tilePainter.usingTile());
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
	// --- Selected Tile ------------------------------------------
	// Number of tiles behind cursor
	sf::Vector2f tilesBehind =
		ng::divVec(ng::subsVec(ng::Cursor::getPosition(), distFromStart_), lineDistance_);;

	// exat position of the highlight
	sf::Vector2f selectedPosition = { distFromStart_.x + lineDistance_.x * static_cast<int>(tilesBehind.x),
									  distFromStart_.y + lineDistance_.y * static_cast<int>(tilesBehind.y) };

	drawSelected_ = true;
	selectedTile_.setSize(lineDistance_);
	selectedTile_.setPosition(selectedPosition);
}

void EditableMap::move(const sf::Vector2f& offset)
{
	Map::move(offset);
	updateGrid();
}
