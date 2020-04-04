#pragma once
#include "NGin.h"
#include "Levels.h"

#include "Music/Music.h"

class MenuLevel : public ng::Level {
public:
	MenuLevel();

	void handleEvents(const sf::Event& event);
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	void setupButtonsStyle(const sf::Texture& texture, 
						   const sf::Font& font,
						   const unsigned fontSize,
						   const sf::Color& themeColor);

	std::shared_ptr<sf::Font> font_;
	std::shared_ptr<sf::Texture> buttonTexture_;
	std::shared_ptr<sf::Texture> backgroundTexture_;

	ng::Button startButton_{ "Start Game", {430, 50} };
	ng::Button settingsButton_ { "Settings", {430, 50} };
	ng::Button editorButton_{ "Editor", {430, 50} };
	ng::Button exitButton_ { "Exit Game", {430, 50} };

	sf::Sprite background_;
};