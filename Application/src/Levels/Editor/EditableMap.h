#pragma once
#include "EditableMap.h"
#include "../Common/Map.h"
#include "../Common/GameDetails.h"

class EditableMap : public Map {
public:
	EditableMap();

	void setMapFile(const MapFile &mapFile);
	void toolCalculations();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	// Setters
	void setScale(const sf::Vector2f& scale);
	void setPosition(const sf::Vector2f& position);
	void move(const sf::Vector2f& offset);
	void setOrigin(const sf::Vector2f& origin);
	void setGridIsActive(const bool gridIsActive) { gridIsActive_ = gridIsActive; }

	// Getters
	bool getGridIsActive() { return gridIsActive_; }

private:
	struct Line {
		Line() {}
		Line(const sf::Vertex& p1, const sf::Vertex& p2) {
			point1 = p1;
			point2 = p2;
		}

		sf::Vertex point1; // point one
		sf::Vertex point2; // point one
	};

	bool gridIsActive_ = true;
	std::vector<Line> gridLines_;

	sf::RectangleShape selectedTile;
};