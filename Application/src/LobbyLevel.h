#pragma once
#include "NGin.h"
#include "Levels.h"

#include <array>

#include "Style.h"

#include "MapFile.h"
#include "SettingsFile.h"
#include "GameDetailsFile.h"

#include "PlayerLine.h"
#include "NPCLine.h"
#include "MapSelector.h"

class LobbyLevel : private GameDetailsFile, public ng::Level {
public:
	LobbyLevel();

	void handleEvents(const sf::Event& event);
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	// Resources
	ng::FontPtr primaryFont_ = NG_FONT_SPTR(location::PRIMARY_FONT);
	ng::TexturePtr backgroundTexture_ = NG_TEXTURE_SPTR(location::LOBBY_BG);

	// Background
	sf::Sprite background_{ *backgroundTexture_ };

	// Navigation buttons 
	ng::Button backButton_{
		primaryFont_,
		"Back",
		size::MEDIUM_FONT_SIZE,
		{ color::FONT_COLOR_R, color::FONT_COLOR_G, color::FONT_COLOR_B},
		{ size::BUTTON_WIDTH, size::BUTTON_HEIGHT},
		NG_TEXTURE_SPTR(location::BUTTON),
		{ color::SELECT_COLOR_R, color::SELECT_COLOR_G, color::SELECT_COLOR_B },
		{ 105, 965 } // position
	};
	
	ng::Button playButton_{
		"Play",
		backButton_,
		{ 735.0F, 965.0F } // position
	};

	sf::Text playerText_{
		"Player:",
		*primaryFont_,
		size::MEDIUM_FONT_SIZE
	};

	sf::Text relativeColorText_{
		"Team Relative Colors",
		*primaryFont_,
		size::MEDIUM_FONT_SIZE
	};

	// Input Lines
	PlayerLine playerLine_{ { 60.0F, 95.0F } }; // object for player

	std::array<NPCLine, GameDetailsFile::maxNumberOfNPCs> npcLines_; // objects for NPC's
	const float npcLineYOffset_ = 195.0F;

	// Map Selector
	MapSelector mapSelector_{ { 1370.0F, 65.0F }, {1.0F, 1.0F} };
	 
	// Nr of NPC's dropdown
	ng::Dropdown npcsDropdown_{
		primaryFont_,
		{ color::FONT_COLOR_R, color::FONT_COLOR_G, color::FONT_COLOR_B },
			size::MEDIUM_FONT_SIZE,
		{ color::HIGHLIGHT_COLOR_R, color::HIGHLIGHT_COLOR_G,
		  color::HIGHLIGHT_COLOR_B, color::HIGHLIGHT_COLOR_A },
		{ color::SELECT_COLOR_R, color::SELECT_COLOR_G, color::SELECT_COLOR_B },
		{ size::SMALL_DROPDOWN_WIDTH, size::SMALL_DROPDOWN_HEIGHT },
		NG_TEXTURE_SPTR(location::SMALL_DROPDOWN),
		{ 45.0F, 175.0F } // position
	};

	// To toggle team-relative color mode
	ng::Switcher relativeColorSwitcher_ {
		{ 59.0F , 54.0F }, // button size
		{ 71.0F, 80.0F }, // mark size
		NG_TEXTURE_SPTR(location::BLOCK_SWTICH),
		{ 95.0F , 800.0F }, // position
		{ 1.0F, 1.0F }, // scale
		{ color::SELECT_COLOR_R, color::SELECT_COLOR_G, color::SELECT_COLOR_B }
	};
};