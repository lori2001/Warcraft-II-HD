#include "Menu.h"
#include <iostream>

void Menu::Setup(sf::RenderWindow & window)
{
	mainmenu.setTransform();
	options.setTransform();
}

void Menu::handleInput(sf::RenderWindow & window, const sf::Event & event)
{
	mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window)); //gets mouse position relative to window

	if (options.isActive)
	{
		options.handleInput(event, mouse);

		if (options.B0getActive())
		{
			options.B0setActive(false);
			options.isActive = false;
			mainmenu.isActive = true;
		}
		else if (options.B1getActive())
		{
			options.B1setActive(false);
			//options.isActive = false;
		}
	}
	if (mainmenu.isActive)
	{
		mainmenu.handleInput(event, mouse);

		if (mainmenu.B0getActive())
		{
			mainmenu.B0setActive(false);
			mainmenu.isActive = false;
		}
		else if (mainmenu.B1getActive())
		{
			mainmenu.B1setActive(false);
			mainmenu.isActive = false;
		}
		else if (mainmenu.B2getActive())
		{
			mainmenu.B2setActive(false);
			mainmenu.isActive = false;
			options.isActive = true;
		}
		else if (mainmenu.B3getActive())
		{
			mainmenu.B3setActive(false);
			window.close();
		}
	}
}

void Menu::Update(sf::RenderWindow & window)
{
	if (options.isActive)
	{
		options.animateGears();
	}
}

void Menu::Compose(sf::RenderWindow & window)
{
	if (options.isActive)
		window.draw(options);
	if(mainmenu.isActive)
		window.draw(mainmenu);
}
