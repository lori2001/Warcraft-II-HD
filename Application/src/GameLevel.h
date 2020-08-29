#pragma once
#include "NGin.h"
#include "Style.h"

#include "GameDetailsFile.h"
#include "Music.h"

#include "GameMenu.h"
#include "Gameplay.h" // actual game elements
#include "CommandPanel.h"

class GameLevel : public ng::Level {
public:
	GameLevel();

	void handleEvents(const sf::Event& event);
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	~GameLevel();

private:
	ng::FontPtr primaryFont_ = NG_FONT_SPTR(location::PRIMARY_FONT);
	
	// the texture HUD that separates gameplay viewport, minimap and buttons
	ng::TexturePtr interfaceTexture_ = NG_TEXTURE_SPTR(location::IN_GAME_INTERFACE);
	sf::Sprite interface_{*interfaceTexture_};

	bool menuTriggerEvent(const sf::Event& event) { // menu toggle event
		return event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape;
	}
	ng::Button menuButton_ // menu toggle button
	{
		NG_FONT_SPTR(location::PRIMARY_FONT),
		"Menu",
		size::MEDIUM_FONT_SIZE,
		{ color::FONT_COLOR_R, color::FONT_COLOR_G, color::FONT_COLOR_B},
		{ size::BUTTON_WIDTH, size::BUTTON_HEIGHT},
		NG_TEXTURE_SPTR(location::BUTTON),
		{ color::SELECT_COLOR_R, color::SELECT_COLOR_G, color::SELECT_COLOR_B },
		{ 20.0F, 1010.0F }, // position
		{ 0.55F, 1.0F } // scale
	};

	// the game's menu (in dynamic memory, should not be always loaded)
	GameMenu* gameMenu_ = nullptr;
	
	// the main display of unit control an gameplay
	Gameplay gameplay_;

	// the command panel
	CommandPanel commandPanel_;
};
