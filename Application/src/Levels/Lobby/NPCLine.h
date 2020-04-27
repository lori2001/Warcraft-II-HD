#pragma once
#include "NGin.h"
#include "../../Style.h"

#include "../../Files/GameDetailsFile.h"

class NPCLine : private GameDetailsFile, public sf::Drawable {
public:
	NPCLine(const sf::Vector2f& position = { 0, 0 });

	void handleEvents(const sf::Event& event, const sf::Vector2f& mouse, const int index);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void setPosition(const sf::Vector2f& position);

	// assumes all dropdowns are in the same horizontal line
	//         and have the same height
	float getHeight() const { return raceDropdown_.getClosedGlobalBounds().height; }

	// setup values by taking indexed information from GameDetailsFile
	void setupValuesWithIndex(const int index);

private:
	ng::Dropdown raceDropdown_{
		NG_FONT_SPTR(location::PRIMARY_FONT), // font
		{ color::FONT_COLOR_R, color::FONT_COLOR_G, color::FONT_COLOR_B }, // font color
		size::SMALL_FONT_SIZE, // font size
		{ color::HIGHLIGHT_COLOR_R, color::HIGHLIGHT_COLOR_G,
		color::HIGHLIGHT_COLOR_B, color::HIGHLIGHT_COLOR_A}, // highlight color
		{ color::SELECT_COLOR_R, color::SELECT_COLOR_G, color::SELECT_COLOR_B }, // select color
		{ size::DROPDOWN_WIDTH, size::DROPDOWN_HEIGHT }, // size
		NG_TEXTURE_SPTR(location::DROPDOWN), // texture
		{ 0, 0 }, // position not yet known
		{ 0.65F, 0.85F } // scale
	};

	// distance between each vertical line of dropdowns
	const float dropdownXOffset_ = 50;
	ng::Dropdown teamDropdown_{ raceDropdown_ }; // inherit same style...
	ng::Dropdown colorDropdown_{ raceDropdown_ };
	ng::Dropdown difficultyDropdown_{ raceDropdown_ };
};
