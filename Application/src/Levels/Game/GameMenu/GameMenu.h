#pragma once
#include "NGin.h"

#include "GameSettings.h"

class GameMenu : public ngin::Level {
public:
	GameMenu();

	void setup();
	void handleEvents(const sf::Event& event);
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	enum RESPONSE {
		NONE = 50, // avoid response collision
		CONTINUE,
		MAIN_MENU,
		EXIT,
	};

private:
	void setupUIStyle(const sf::Font& font, const unsigned fontSize, const sf::Color& themeColor);

	std::shared_ptr<sf::Texture> buttonTexture_;
	std::shared_ptr<sf::Texture> sliderTexture_;
	std::shared_ptr<sf::Texture> backgroundTexture_;
	std::shared_ptr<sf::Font>    warcraftFont_;
	
	sf::Text menuText_;

	ngin::Button continueButton_{ "Continue Playing", {430, 50} };
	ngin::Button settingsButton_{ "Settings", {430, 50} };
	ngin::Button mainMenuButton_{ "Back To Main Menu", {430, 50} };
	ngin::Button exitButton_{ "Exit to Windows", {430, 50} };

	GameSettings gameSettings_;
	bool settingsIsActive; 

	sf::Sprite background_;
};