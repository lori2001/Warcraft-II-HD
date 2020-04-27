#pragma once
#include "NGin.h"
#include "../../Style.h"

#include "../../Files/SettingsFile.h"
#include "../Levels.h"

class EditorMenu : public ng::Level {
public:
	EditorMenu();
	void handleEvents(const sf::Event& event);
	void update();

	void drawBackground(sf::RenderTarget& target) const;
	// draws elements
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	// menu height in pixels
	static constexpr const float menuHeightPx = 80.0F;
	// menu height in percentage
	static constexpr const float menuHeightPer = menuHeightPx / MAIN_VIEW_HEIGHT;

private:
	ng::TexturePtr headerTexture_ = NG_TEXTURE_SPTR(location::EDITOR_HEADER);
	sf::Sprite header_{*headerTexture_};

	// goes back to main menu
	ng::Button backButton_{
		{ 75.0F, 75.0F }, // position
		NG_TEXTURE_SPTR(location::LEAVE_BUTTON)
	};

	// "File" dropdown
	ng::Dropdown fileDropdown_{
		NG_FONT_SPTR(location::SECONDARY_FONT),
		{ color::FONT_COLOR_R, color::FONT_COLOR_G, color::FONT_COLOR_B },
		size::MEDIUM_FONT_SIZE,
		{ color::HIGHLIGHT_COLOR_R, color::HIGHLIGHT_COLOR_G,
		  color::HIGHLIGHT_COLOR_B, color::HIGHLIGHT_COLOR_A},
		{ color::SELECT_COLOR_R, color::SELECT_COLOR_G, color::SELECT_COLOR_B },
		{ size::DROPDOWN_WIDTH, size::DROPDOWN_HEIGHT }, 
		NG_TEXTURE_SPTR(location::DROPDOWN),
		{ 160.0F , 20.0F } // position
	};
};