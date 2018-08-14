#include "Menu.h"
#include <iostream>

void Menu::Setup(sf::RenderWindow & window)
{
	menuworks.setTexture(loading.buttonT,loading.warcraftF);
}

void Menu::handleInput(sf::RenderWindow & window, const sf::Event & event)
{
	mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window)); //gets mouse position relative to window

	menuworks.setSelected(mouse);
	menuworks.handleInput(event,loading.pressbutton);
}

void Menu::Update(sf::RenderWindow & window)
{
}

void Menu::Compose(sf::RenderWindow & window)
{
	window.draw(menuworks);
}
