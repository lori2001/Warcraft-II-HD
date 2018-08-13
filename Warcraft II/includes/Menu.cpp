#include "Menu.h"
#include <iostream>

void Menu::Setup(sf::RenderWindow & window)
{
	menuworks.setFillColor(sf::Color::Red);
}

void Menu::handleInput(sf::RenderWindow & window, const sf::Event & event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		menuworks.move(5, 0);
	}
}

void Menu::Update(sf::RenderWindow & window)
{
	if (menuworks.getFillColor() == sf::Color::Red)
		menuworks.setFillColor(sf::Color::Blue);
	else if (menuworks.getFillColor() == sf::Color::Blue)
		menuworks.setFillColor(sf::Color::Red);
}

void Menu::Compose(sf::RenderWindow & window)
{
	window.draw(menuworks);
}
