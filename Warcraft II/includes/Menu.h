#pragma once
#include "SFML\Graphics.hpp"
#include "RW/Settings.h"
#include "RW/Loading.h"
#include "RW/MapReader.h"
#include "Screens/MainMenu.h"
#include "Screens/Singleplayer.h"
#include "Screens/Multiplayer.h"
#include "Screens/Options.h"
#include "Screens/Popup.h"
#include "Others/Players.h"

class Menu
{
private:
	sf::Vector2f mouse; //holds position of the mouse

	RW::Settings settings;
	RW::Loading loading;
	RW::MapReader mapreader;

	UI::MapSelector test;

	Players players;

	Screens::MainMenu mainmenu;
	Screens::Singleplayer singleplayer;
	Screens::Multiplayer multiplayer;
	Screens::Options options;

	Screens::Popup reswarning{2};

	std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes(); //holds all the possible resolutions for current screen
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