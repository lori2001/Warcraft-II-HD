#pragma once
#include "NGin.h"
#include "../../../Style.h"
#include "../../Levels.h"

#include "GameSettings.h"

class GameMenu : public ng::Level {
public:
	GameMenu();

	void handleEvents(const sf::Event& event);
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	bool shouldClose() { return continueButton_.isActive(); }

private:
	ng::FontPtr primaryFont_ = NG_FONT_SPTR(location::PRIMARY_FONT);
	sf::Text menuText_{ "In-Game Menu", *primaryFont_, 40 };

	ng::TexturePtr backgroundTexture_ = NG_TEXTURE_SPTR(location::IN_GAME_MENU_BG);
	sf::Sprite background_{ *backgroundTexture_ };

	ng::Button continueButton_
	{
		primaryFont_,
		"Continue Playing",
		size::MEDIUM_FONT_SIZE,
		{ color::FONT_COLOR_R, color::FONT_COLOR_G, color::FONT_COLOR_B},
		{ size::BUTTON_WIDTH, size::BUTTON_HEIGHT},
		NG_TEXTURE_SPTR(location::BUTTON),
		{ color::SELECT_COLOR_R, color::SELECT_COLOR_G, color::SELECT_COLOR_B },
		{ 745.0F, 330.0F }, // pos
		{ 1.0F, 1.25F } // scale
	};

	ng::Button settingsButton_{
		"Settings",
		continueButton_,
		{ 745, 430 }
	};

	ng::Button mainMenuButton_{
		"Back To Main Menu",
		continueButton_,
		{ 745, 730 }
	};

	ng::Button exitButton_{
		"Exit to Windows",
		continueButton_,
		{ 745, 830 }
	};

	//GameSettings gameSettings_;
	//bool settingsIsActive; 
};