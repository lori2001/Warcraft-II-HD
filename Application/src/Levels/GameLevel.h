#pragma once
#include "NGin.h"
#include "Levels.h"

// external
#include "Common/GameDetails.h"

#include "Music/Music.h"
#include "Game/GameMenu/GameMenu.h"

class GameLevel : public ng::Level {
public:
	GameLevel();

	void handleEvents(const sf::Event& event);
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	void setupUIStyle(const sf::Font& font, const unsigned fontSize, const sf::Color& themeColor);

	std::shared_ptr<sf::Texture> buttonTexture_;
	std::shared_ptr<sf::Texture> interfaceTexture_;
	std::shared_ptr<sf::Font>    warcraftFont_;
	
	sf::Sprite interface_;

	ng::Button menuButton_{ "Menu", {430, 50} };
	bool menuIsActive = false;

	// ng::Level* menu_;
};