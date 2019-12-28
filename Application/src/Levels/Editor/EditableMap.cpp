#include "EditableMap.h"
#include "nfd.h"

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

	tileMark.setFillColor(sf::Color(255, 0, 0));
	tileMark.setSize({Map::getTileSize().x * Map::getScale().x, Map::getTileSize().y * Map::getScale().y});
	tileMark.setPosition({ Map::getPosition().x + Map::getScaledSize().x, Map::getPosition().y + Map::getScaledSize().y });
}

void EditableMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	Map::draw(target, states);
	// TODO: Fix This!
	// target.draw(tileMark);
}

void EditableMap::setScale(const sf::Vector2f& scale)
{
	Map::setScale(scale);
	tileMark.setScale(scale);
}

void EditableMap::setPosition(const sf::Vector2f& position)
{
	Map::setPosition(position);
	tileMark.setPosition({ Map::getPosition().x + Map::getScaledSize().x, Map::getPosition().y + Map::getScaledSize().y });
}

void EditableMap::setOrigin(const sf::Vector2f& origin)
{
	Map::setOrigin(origin);
	tileMark.setOrigin(origin);
}

void EditableMap::move(const sf::Vector2f& offset)
{
	Map::move(offset);
	tileMark.move(offset);
}
