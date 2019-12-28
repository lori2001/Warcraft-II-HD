#pragma once
#include "EditableMap.h"
#include "../Common/Map.h"
#include "../Common/GameDetails.h"

class EditableMap : public Map {
public:
	void setMapFile(const MapFile &mapFile);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void setScale(const sf::Vector2f& scale);
	void setPosition(const sf::Vector2f& position);
	void setOrigin(const sf::Vector2f& origin);
	void move(const sf::Vector2f& offset);

private:
	sf::RectangleShape tileMark;
};