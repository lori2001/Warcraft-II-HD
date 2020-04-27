#pragma once
#include "NGin.h"

#include "../Style.h"
#include "Levels.h"
#include "../Files/SettingsFile.h"

#include "Music/Music.h"

class MenuLevel : public ng::Level {
public:
	MenuLevel();

	void handleEvents(const sf::Event& event);
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	
	ng::Button startButton_
	{
		NG_FONT_SPTR(location::PRIMARY_FONT),
		"Start Game",
		size::MEDIUM_FONT_SIZE,
		{ color::FONT_COLOR_R, color::FONT_COLOR_G, color::FONT_COLOR_B},
		{ size::BUTTON_WIDTH, size::BUTTON_HEIGHT},
		NG_TEXTURE_SPTR(location::BUTTON),
		{ color::SELECT_COLOR_R, color::SELECT_COLOR_G, color::SELECT_COLOR_B },
		{ MAIN_VIEW_XCENTER - size::BUTTON_WIDTH / 2, MAIN_VIEW_YCENTER - 3 * size::BUTTON_HEIGHT }
	};

	ng::Button settingsButton_{
		"Settings",
		startButton_,
		{ MAIN_VIEW_XCENTER - size::BUTTON_WIDTH / 2, MAIN_VIEW_YCENTER - 1.5F * size::BUTTON_HEIGHT }
	};

	ng::Button editorButton_{
		"Editor",
		startButton_,
		{ MAIN_VIEW_XCENTER - size::BUTTON_WIDTH / 2, MAIN_VIEW_YCENTER + 0 * size::BUTTON_HEIGHT }
	};
	
	ng::Button exitButton_{
		"Exit Game",
		startButton_,
		{ MAIN_VIEW_XCENTER - size::BUTTON_WIDTH / 2, MAIN_VIEW_YCENTER + 1.5F * size::BUTTON_HEIGHT }
	};

	sf::Sprite background_;
	std::shared_ptr<sf::Texture> backgroundTexture;
};