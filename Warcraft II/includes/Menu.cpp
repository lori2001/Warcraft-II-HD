#include "Menu.h"
#include <iostream>

void Menu::Setup(sf::RenderWindow & window)
{
	// set options slider levels to levels in settings.json
	options.S0setLevel(settings.getMusic());
	options.S1setLevel(settings.getSoundFX());

	mainmenu.setTransform();
	multiplayer.setTransform();
	options.setTransform();
	options.setText(modes);

	reswarning.setScale(settings.get1920Scale());
	reswarning.setPosition(sf::Vector2f(float(settings.getRes().x / 2), float(settings.getRes().y / 2)));
	reswarning.setDescription(0, "Please press OK to keep the resolution,\nCancel to revert it.");
	reswarning.setDescription(1, "Reverting in:");
	reswarning.setDescriptionPos(1, sf::Vector2f(0.5f, 0.68f));
	reswarning.setCountdownpos(sf::Vector2f(0.65f,0.68f));
}

void Menu::handleInput(sf::RenderWindow & window, const sf::Event & event)
{
	mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window)); //gets mouse position relative to window

	if (reswarning.isActive)
	{
		reswarning.handleInput(event, mouse);

		if (reswarning.B0getActive() || reswarning.countdownOver == true)
		{
			reswarning.isActive = false;
			options.isActive = true;

			//make new values equal old ones
			settings.setRes(settings.getOldRes());
			settings.setFullscreen(settings.getOldFullscreen());

			//apply old resolution to window
			settings.setWindow(window);

			//reset proper scales
			this->Setup(window);

			//resets this bool so it can be used in later instances
			reswarning.countdownOver = false;
			reswarning.B0setActive(false);
		}
		else if (reswarning.B1getActive())
		{
			reswarning.isActive = false;
			options.isActive = true;

			//make old values equal new ones
			settings.setOldRes(settings.getRes());
			settings.setOldFullscreen(settings.getFullscreen());

			//resets this bool so it can be used in later instances
			reswarning.countdownOver = false;
			reswarning.B1setActive(false);
		}
	}
	else if(multiplayer.isActive)
	{
		multiplayer.handleInput(event, mouse);

		if (multiplayer.B0getActive())
		{
			multiplayer.B0setActive(false);
			multiplayer.isActive = false;
			mainmenu.isActive = true;
		}
	}
	else if (options.isActive)
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
				//apply new resolution to window
				settings.setWindow(window);

				//set proper scales
				this->Setup(window);

				//open warning ro revert in case something goes wrong with changing the resolution
				reswarning.isActive = true;
				reswarning.restartTimining();
				options.isActive = false;
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
			mainmenu.isActive = false;
			multiplayer.isActive = true;
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
	if (reswarning.isActive)
	{
		options.animateGears();
		reswarning.animateCountdown();
	}
	else if (options.isActive)
	{
		options.animateGears();
	}
}

void Menu::Compose(sf::RenderWindow & window)
{
	//Playing sounds
	if (loading.menusong.getStatus() != sf::Music::Status::Playing)
		loading.menusong.play();

	if (reswarning.isActive)
	{
		window.draw(options);
		window.draw(reswarning);
	}
	else if(multiplayer.isActive)
		window.draw(multiplayer);
	else if (options.isActive)
		window.draw(options);
	else if(mainmenu.isActive)
		window.draw(mainmenu);

}
