#include "Menu.h"
#include <iostream>

void Menu::Setup(sf::RenderWindow & window)
{
	// set options slider levels to levels in settings.json
	options.S0setLevel(settings.getMusic());
	options.S1setLevel(settings.getSoundFX());

	mainmenu.setTransform();
	options.setTransform();
	options.setText(modes);
}

void Menu::handleInput(sf::RenderWindow & window, const sf::Event & event)
{
	mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window)); //gets mouse position relative to window

	if (options.isActive)
	{
		options.handleInput(event, mouse);

		if (options.B0getActive()) // if "back" is pressed
		{
			//resets changes made but not applied
			settings.setRes(settings.getOldRes());
			settings.setFullscreen(settings.getOldFullscreen());

			//applies it on-screen
			options.setText(modes);

			//makes button inactive
			options.B0setActive(false);

			//goes back to mainmenu
			options.isActive = false;
			mainmenu.isActive = true;
		}
		else if (options.B1getActive())
		{
			// if either the res or the fullscreen has changed
			if (settings.getOldFullscreen() != settings.getFullscreen() || settings.getOldRes() != settings.getRes())
			{
				//make new and old values equal
				settings.setOldRes(settings.getRes());
				settings.setOldFullscreen(settings.getFullscreen());

				//apply new resolution to window
				settings.setWindow(window);

				//reset proper scales
				this->Setup(window);
			}
			//sets button back to inactive
			options.B1setActive(false);
		}
		else if (options.S0getActive()) // if the level has changed
		{
			settings.setMusic(options.S0getLevel()); //set the settings value to level 
			loading.setMusicVolume(10 * settings.getMusic()); //set musics value to the new settings value
			options.setText(modes); //update text visually

			options.S0setActive(false);
		}
		else if (options.S1getActive()) // if the level has changed
		{
			settings.setSoundFX(options.S1getLevel()); //set the settings value to level 
			loading.setSFXVolume(10 * settings.getSoundFX()); //set soundfxs value to the new settings value
			options.setText(modes); //update text visually

			options.S1setActive(false);
		}
		for (short int i = 1; i < 8; i++)
		{
			if (i < 3 && options.D1getActive(i))
			{
				settings.setOldFullscreen(settings.getFullscreen());
				options.D1setActive(i, false);

				if (i == 1)
					settings.setFullscreen(true);
				else if (i == 2)
					settings.setFullscreen(false);

				//the text has changed, it has to be set
				options.setText(modes);
			}
			if (i < 8 && options.D0getActive(i))
			{
				settings.setOldRes(settings.getRes());
				options.D0setActive(i, false);
				sf::VideoMode mode = modes[i - 1];

				settings.setRes(sf::Vector2i(mode.width, mode.height));

				//the text has changed, it has to be set
				options.setText(modes);
			}
		}
	}
	else if (mainmenu.isActive)
	{
		mainmenu.handleInput(event, mouse);

		if (mainmenu.B0getActive()) //singleplayer
		{
			mainmenu.B0setActive(false);
			//mainmenu.isActive = false;
		}
		else if (mainmenu.B1getActive()) //multiplayer
		{
			mainmenu.B1setActive(false);
			//mainmenu.isActive = false;
		}
		else if (mainmenu.B2getActive()) //options
		{
			mainmenu.B2setActive(false);
			mainmenu.isActive = false;
			options.isActive = true;
		}
		else if (mainmenu.B3getActive()) //exit game
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
	//Playing sounds
	if (loading.menusong.getStatus() != sf::Music::Status::Playing)
		loading.menusong.play();

	//Drawing
	if (options.isActive)
		window.draw(options);
	if(mainmenu.isActive)
		window.draw(mainmenu);
}
