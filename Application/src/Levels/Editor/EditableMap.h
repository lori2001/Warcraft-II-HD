#pragma once
#include "EditableMap.h"
#include "../Common/Map.h"
#include "../Common/GameDetails.h"
#include "../Editor/TilePainter.h"

class EditableMap : public Map {
public:
	EditableMap();

	bool setMapFile();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void handleEvents(const sf::Event& event, const TilePainter& tilePainter);

	// Setters
	void setScale(const sf::Vector2f& scale);
	void setPosition(const sf::Vector2f& position);
	void move(const sf::Vector2f& offset);
	void setOrigin(const sf::Vector2f& origin);
	void setGridIsActive(const bool gridIsActive) {
		gridIsActive_ = gridIsActive;
		if (gridIsActive_) {
			updateGrid();
		}
	}

	// Getters
	bool getGridIsActive() { return gridIsActive_; }
	sf::Vector2f getSelectedTilePos() { return selectedTile_.getPosition(); }

	bool isFocused() const { return isFocused_; }
	void checkIfFocused(const bool toolbarFocus) {
		if (!toolbarFocus && ng::Main::windowHasFocus()) { isFocused_ = true; }
		else { isFocused_ = false; }
	}
	// if nothing else but the window is focused then this surely is
	void checkIfFocused(const bool toolbarFocus, const bool tilePainterFocus) {
		if (!toolbarFocus && !tilePainterFocus && ng::Main::windowHasFocus()) {isFocused_ = true;}
		else {isFocused_ = false;}
	}
private:
	void undoChange();
	void redoChange();
	
	void updateGrid();
	void adjustSelectedTile();

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
	sf::Vector2i selectedTileCoords_; // the coordinates of a given tile when added in matrix
	bool drawSelected_ = true;
	bool mouseHeld_ = false; // true if tiles need to be placed

	// properties
	sf::Vector2f topLeft_ ;
	sf::Vector2f bottomRight_ ;
	sf::Vector2f lineDistance_;
	sf::Vector2f numOfTiles_;
	sf::Vector2f distFromStart_;

	// change logging
	// 3 element vector representing changes x,y = coordinates, z = tileNumber
	std::vector<sf::Vector3i> logs_;
	// index representing last change
	int lastChange_;
};