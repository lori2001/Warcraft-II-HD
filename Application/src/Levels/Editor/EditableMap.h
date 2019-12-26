#pragma once
#include "EditableMap.h"
#include "../Common/Map.h"
#include "../Common/GameDetails.h"

class EditableMap : public Map {
public:
	void setMapFile(const MapFile &mapFile);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:

	sf::RectangleShape tileMark;
};