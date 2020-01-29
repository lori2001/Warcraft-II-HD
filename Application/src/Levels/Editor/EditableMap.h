#pragma once
#include "EditableMap.h"
#include "../Common/Map.h"
#include "../Common/GameDetails.h"
#include "../Editor/TilePainter.h"

class EditableMap : public Map {
public:
	EditableMap();

	bool setMapFile(const MapFile &mapFile);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void updateGrid();
	void handleEvents(const sf::Event& event, const TilePainter& tilePainter);

	// Setters
	void setScale(const sf::Vector2f& scale);
	void setPosition(const sf::Vector2f& position);
	void move(const sf::Vector2f& offset);
	void setOrigin(const sf::Vector2f& origin);
	void setGridIsActive(const bool gridIsActive) { gridIsActive_ = gridIsActive; }

	// Getters
	bool getGridIsActive() { return gridIsActive_; }
	sf::Vector2f getSelectedTilePos() { return selectedTile_.getPosition(); }

	bool isFocused() const { return isFocused_; }
	void checkIfFocused(const bool toolbarFocus) {
		if (!toolbarFocus && ngin::MainLevel::windowHasFocus()) { isFocused_ = true; }
		else { isFocused_ = false; }
	}
	// if nothing else but the window is focused then this surely is
	void checkIfFocused(const bool toolbarFocus, const bool tilePainterFocus) {
		if (!toolbarFocus && !tilePainterFocus && ngin::MainLevel::windowHasFocus()) {isFocused_ = true;}
		else {isFocused_ = false;}
	}
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

	bool isFocused_ = false;
	// an imaginary box that contains the current size of the editable map at given time
	sf::FloatRect virtualBox_;

	bool gridIsActive_ = true;
	std::vector<Line> gridLines_;

	sf::RectangleShape selectedTile_;
	bool drawSelected_ = true;

	// properties
	sf::Vector2f topLeft_ ;
	sf::Vector2f bottomRight_ ;
	sf::Vector2f lineDistance_;
	sf::Vector2f numOfTiles_;
	sf::Vector2f distFromStart_;

};