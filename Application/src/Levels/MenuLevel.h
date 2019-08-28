#pragma once
#include "NGin.h"
#include "Music/Music.h"

class MenuLevel : public ngin::Level {
public:
	MenuLevel() { setup(); }

	void setup();
	void handleEvents(const sf::Event& event);
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	enum RESPONSE {
		NONE = 0,
		START,
		OPTIONS,
		EDITOR,
		EXIT
	};
private:
	void setupButtonsStyle(const sf::Texture& texture, 
						   const sf::Font& font,
						   const unsigned fontSize,
						   const sf::Color& themeColor);

	std::shared_ptr<sf::Font> font_;
	std::shared_ptr<sf::Texture> buttonTexture_;
	std::shared_ptr<sf::Texture> backgroundTexture_;

	ngin::Button startButton_{ "Start Game", {430, 50} };
	ngin::Button settingsButton_ { "Settings", {430, 50} };
	ngin::Button editorButton_{ "Editor", {430, 50} };
	ngin::Button exitButton_ { "Exit Game", {430, 50} };

	sf::Sprite background_;
};