#include "Menu.h"
#include <iostream>

void Menu::Setup(sf::RenderWindow & window)
{
	mainmenu.setTransform();
}

void Menu::handleInput(sf::RenderWindow & window, const sf::Event & event)
{
	mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window)); //gets mouse position relative to window

	mainmenu.handleInput(event,mouse);
}

void Menu::Update(sf::RenderWindow & window)
{
}

void Menu::Compose(sf::RenderWindow & window)
{
	window.draw(mainmenu);
}
