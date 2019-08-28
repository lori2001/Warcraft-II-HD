#pragma once
#include "NGin.h"

// external
#include "Common/GameDetails.h"

#include "Music/Music.h"
#include "Game/GameMenu/GameMenu.h"

// TODO: Remove this
#include "Game/Units/Humans/Footman.h"

class GameLevel : public ngin::Level {
public:
	GameLevel() { setup(); }

	void setup();
	void handleEvents(const sf::Event& event);
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	void setupUIStyle(const sf::Font& font, const unsigned fontSize, const sf::Color& themeColor);

	std::shared_ptr<sf::Texture> buttonTexture_;
	std::shared_ptr<sf::Texture> interfaceTexture_;
	std::shared_ptr<sf::Font>    warcraftFont_;
	
	sf::Sprite interface_;

	Footman testSoldier;

	ngin::Button menuButton_{ "Menu", {430, 50} };
	bool menuIsActive = false;

	ngin::Level* menu_;
};