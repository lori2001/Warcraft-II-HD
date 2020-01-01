#include "EditableMap.h"
#include "nfd.h"

EditableMap::EditableMap()
{
	selectedTile.setFillColor(sf::Color(255,255,0,100));
}

void EditableMap::setMapFile(const MapFile& mapFile)
{
	nfdchar_t* outPath = NULL;
	nfdresult_t result = NFD_OpenDialog("mapfile", GameDetails::mapFile.getFolderPath().c_str(), &outPath);

	if (result == NFD_OKAY) {
		GameDetails::mapFile.read(outPath);
		NG_LOG_INFO(GameDetails::mapFile.getMapName());
	}
	else if (result == NFD_ERROR) {
		NG_LOG_ERROR("Error: %s\n", NFD_GetError());
	}

	Map::setMapFile(GameDetails::mapFile);
}

void EditableMap::toolCalculations()
{
	// --- Grid Calculations --------------------------------------
	// deletes old grid lines before recalculating them
	sf::Vector2f topLeft = {
		getPosition().x - getScaledSize().x / 2, getPosition().y - getScaledSize().y / 2 };
	sf::Vector2f bottomRight = {
		getPosition().x + getScaledSize().x / 2, getPosition().y + getScaledSize().y / 2 };

	sf::Vector2f lineDistance = {
		Map::getTileSize().x * Map::getScale().x,
		Map::getTileSize().y * Map::getScale().y };

	sf::Vector2f numOfTiles = ngin::divVec(topLeft, lineDistance);

	sf::Vector2f distFromStart = { topLeft.x - lineDistance.x * static_cast<int>(numOfTiles.x),
								   topLeft.y - lineDistance.y * static_cast<int>(numOfTiles.y) };

	if (gridIsActive_) {
		gridLines_.clear();

		for (float x = distFromStart.x; x <= ngin::MainLevel::view_.getSize().x; x += lineDistance.x) {
			Line XLine{
				sf::Vertex(sf::Vector2f(x, 0)),
				sf::Vertex(sf::Vector2f(x, ngin::MainLevel::view_.getSize().y))
			};

			gridLines_.push_back(XLine);
		}
		for (float y = distFromStart.y; y <= ngin::MainLevel::view_.getSize().y; y += lineDistance.y) {
			Line YLine{
				sf::Vertex(sf::Vector2f(0, y)),
				sf::Vertex(sf::Vector2f(ngin::MainLevel::view_.getSize().x, y))
			};

			gridLines_.push_back(YLine);
		}
	}
	// ------------------------------------------------------------

	// Number of tiles behind cursor
	sf::Vector2f tilesBehind =
		ngin::divVec(ngin::subsVec(ngin::Cursor::getPosition(), distFromStart), lineDistance);;

	// exat position of the highlight
	sf::Vector2f selectedPosition = { distFromStart.x + lineDistance.x * static_cast<int>(tilesBehind.x),
									  distFromStart.y + lineDistance.y * static_cast<int>(tilesBehind.y) };
	
	selectedTile.setSize(lineDistance);
	selectedTile.setPosition(selectedPosition);
}

void EditableMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	Map::draw(target, states);
	target.draw(selectedTile);

	if (gridIsActive_) {
		for (int i = 0; i < gridLines_.size(); i++) {
			sf::Vertex line[] = {
				gridLines_[i].point1,
				gridLines_[i].point2
			};
			target.draw(line, 2, sf::Lines);
		}
	}
}

void EditableMap::setScale(const sf::Vector2f& scale)
{
	Map::setScale(scale);
}

void EditableMap::setPosition(const sf::Vector2f& position)
{
	Map::setPosition(position);
}

void EditableMap::setOrigin(const sf::Vector2f& origin)
{
	Map::setOrigin(origin);
}

void EditableMap::move(const sf::Vector2f& offset)
{
	Map::move(offset);
}
