#pragma once
#include "SFML\Graphics.hpp"
#include "RW/Settings.h"
#include "RW/Loading.h"
#include "Screens/MainMenu.h"
#include "Screens/Options.h"
#include "Screens/Popup.h"

class Menu
{
private:
	sf::Vector2f mouse; //holds position of the mouse

	Screens::MainMenu mainmenu;
	Screens::Options options;
	Screens::Popup test{2};

	RW::Settings settings;
	RW::Loading loading;

	std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
public:
	Menu()
	{
		//this is where the game puts you first
		mainmenu.isActive = true;
	}
	bool isActive = true;

	void Setup(sf::RenderWindow &window);
	void handleInput(sf::RenderWindow &window, const sf::Event &event);
	void Update(sf::RenderWindow &window);
	void Compose(sf::RenderWindow &window);
};