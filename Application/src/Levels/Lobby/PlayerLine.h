#pragma once
#include "NGin.h"
#include "../../Style.h"

#include "../../Files/GameDetailsFile.h"

class PlayerLine : private GameDetailsFile, public sf::Drawable {
public:
	PlayerLine(const sf::Vector2f& position);

	void handleEvents(const sf::Event& event, const sf::Vector2f& mouse);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void setPosition(const sf::Vector2f& position);

	void correctForRelativeColor();

private:
	// Textures and fonts
	const ng::FontPtr primaryFont_ = NG_FONT_SPTR(location::PRIMARY_FONT);

	const float nameTextOffset_ = -43;
	sf::Text nameText_{
		"Name",
		*primaryFont_,
		size::MEDIUM_FONT_SIZE
	};

	ng::InputText nameInput_
	{ NG_TEXTURE_SPTR(location::INPUT_TEXT),
		{size::INPUT_TEXT_WIDTH, size::INPUT_TEXT_HEIGHT},
		primaryFont_,
		{ color::FONT_COLOR_R, color::FONT_COLOR_G, color::FONT_COLOR_B },
		{ color::SELECT_COLOR_R, color::SELECT_COLOR_G, color::SELECT_COLOR_B},
	};

	ng::Dropdown raceDropdown_{
		primaryFont_, // font
		{ color::FONT_COLOR_R, color::FONT_COLOR_G, color::FONT_COLOR_B }, // font color
		size::SMALL_FONT_SIZE, // font size
		{ color::HIGHLIGHT_COLOR_R, color::HIGHLIGHT_COLOR_G,
		color::HIGHLIGHT_COLOR_B, color::HIGHLIGHT_COLOR_A}, // highlight color
		{ color::SELECT_COLOR_R, color::SELECT_COLOR_G, color::SELECT_COLOR_B }, // select color
		{ size::DROPDOWN_WIDTH, size::DROPDOWN_HEIGHT }, // size
		NG_TEXTURE_SPTR(location::DROPDOWN), // texture
		{ 0, 0 }, // position not yet known
		{ 0.70F, 0.85F } // scale
	};

	ng::Dropdown teamDropdown_{ raceDropdown_ }; // inherit same style...
	ng::Dropdown colorDropdown_{ raceDropdown_ };
};