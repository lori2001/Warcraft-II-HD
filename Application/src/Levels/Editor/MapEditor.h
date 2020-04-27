#pragma once
#include "NGin.h"

#include "../../Files/MapFile.h"
#include "../../Files/SettingsFile.h"

#include "EditorMenu.h"

#include "../Common/Map.h"
#include "MapEditor/TilePainter.h"

class MapEditor : public ng::Level {
public:
	// initialize the editor on <filePath> map file
	MapEditor(const std::string& filePath);
	void handleEvents(const sf::Event& event);
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	// called whenever the view changes state
	void updateGrid();
	void updateSelectionPos();
	void placeTile(const int tileIndex);

	// sets the center of view to the center of map
	void centerEditorOnMap() {
		editorView_.setCenter({ Map::getScaledSize().x / 2, Map::getScaledSize().y / 2 });
	}

	// get the saign of a float value (-1 if negative and +1 if positive)
	// 0 returns positive
	int signOf(float a) {
		return ((!signbit(a)) << 1) - 1;
	}

	// ----- Navigation Properties START -------------
	const float editorMoveSpeed_ = 265.0F;
	const float editorZoomFactor_ = 1.12F;
	const float editorMaxZoomFactor_ = 3.0F;
	const float editorMinZoomFactor_ = 1.0F / 9.0F;
	float editorCurrentZoomFactor_ = 1.0F; // DO NOT CHANGE!

	sf::Keyboard::Key keyNavigateUp_ = sf::Keyboard::W;
	sf::Keyboard::Key keyNavigateDown_ = sf::Keyboard::S;
	sf::Keyboard::Key keyNavigateLeft_ = sf::Keyboard::A;
	sf::Keyboard::Key keyNavigateRight_ = sf::Keyboard::D;

	// if these functions are true the view will zoom in/out
	bool zoomInFunction(const sf::Event& event)
	{
		return event.type == sf::Event::MouseWheelMoved && event.mouseWheel.delta < 0 && editorCurrentZoomFactor_ < editorMaxZoomFactor_;
	}
	bool zoomOutFunction(const sf::Event& event)
	{
		return event.type == sf::Event::MouseWheelMoved && event.mouseWheel.delta > 0 && editorCurrentZoomFactor_ > editorMinZoomFactor_ ;
	}
	// ----- Navigation Properties ENDD ----------------

	// -- Grid and Mouse selection START --------------
	// represents the size and position of where things will be drawn by this object
	sf::View editorView_{ sf::FloatRect{
		0,
		0,
		MAIN_VIEW_WIDTH,
		MAIN_VIEW_HEIGHT - EditorMenu::menuHeightPx }
	};

	// important global coordinates of editor view
	sf::Vector2f editorViewTopLeft_, editorViewBottomRight_;

	// unsigned distance in px of the first line from global coordinates of the topLeft of the view 
	sf::Vector2f firstLineDistance_;

	// grid enable/disable
	ng::Switcher gridSwitcher_{
		{ 75.0F , 75.0F }, // button size
		{ 75.0F, 75.0F }, // mark size
		NG_TEXTURE_SPTR(location::GRID_SWITCHER),
		{ 1795.0F, 10.0F }, // position
		{ ng::ftovec(0.8F) }, // scale
		{ color::SELECT_COLOR_R, color::SELECT_COLOR_G, color::SELECT_COLOR_B }
	};
	const sf::Color gridColor_{100, 100, 100};
	sf::VertexArray gridLines_{sf::Lines};

	sf::RectangleShape selectionRect_; // colors the rectangle currently selected by mouse
	bool canPlace_ = false; // if false do not draw selectionRect_ to signal the user that placing tiles isn't possible
	// -- Grid and Mouse selection END ------------------

	// -- Tile Painter -----------------
	ng::Switcher tilePainterSwitcher_{
		{ 75.0F , 75.0F }, // button size
		{ 75.0F, 75.0F }, // mark size
		NG_TEXTURE_SPTR(location::PAINT_SWITCHER),
		{ 1595.0F, 10.0F }, // position
		{ ng::ftovec(0.8F) }, // scale
		{ color::SELECT_COLOR_R, color::SELECT_COLOR_G, color::SELECT_COLOR_B }
	};
	Painter* currentPainter_ = nullptr;

	// --- Extra Buttons/Functions/Properties -----------
	ng::Button recenterButton_{
		{},{},{},{},
		{ 75.0F , 75.0F }, // size
		NG_TEXTURE_SPTR(location::RECENTER_BUTTON),
		{ color::SELECT_COLOR_R, color::SELECT_COLOR_G, color::SELECT_COLOR_B },
		{ 1695.0F, 10.0F }, // position
		{ ng::ftovec(0.8F) } // scale
	};
};