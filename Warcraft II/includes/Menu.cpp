#include "Menu.h"

void Menu::Setup(sf::RenderWindow & window)
{
	// set options slider levels to levels in settings.json
	options.S0setLevel(settings.getMusic());
	options.S1setLevel(settings.getSoundFX());

	players.resetValues(); //set players' values to default

	/*read maps*/
	mapreader.readList(); //read the list of maps
	mapreader.read(); //read the maps in list
	singleplayer.M0setTiles(mapreader);
	/***********/

	/*initialize cursor*/
	cursor.setTexture(loading.cursorT);
	cursor.setScale(settings.get1000Scale());
	/*******************/

	/*initialize screens*/
	mainmenu.setTransform();
	singleplayer.setTransform();
	singleplayer.setText();
	singleplayer.setColors();
	multiplayer.setTransform();
	options.setTransform();
	options.setText(modes);
	/*******************/

	/*initialize popups*/
	reswarning.setScale(settings.get1920Scale());
	reswarning.setPosition(sf::Vector2f(float(settings.getRes().x / 2), float(settings.getRes().y / 2)));
	reswarning.setDescription(0, "Please press OK to keep the resolution,\nCancel to revert it.");
	reswarning.setDescription(1, "Reverting in:");
	reswarning.setDescriptionPos(1, sf::Vector2f(0.5f, 0.68f));
	reswarning.setCountdownPos(sf::Vector2f(0.65f,0.68f));
	/*******************/
}

void Menu::handleInput(sf::RenderWindow & window, const sf::Event & event)
{
	mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window)); //gets mouse position relative to window

	//set position of cursor
	cursor.setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));

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
	else if (singleplayer.isActive)
	{
		singleplayer.handleInput(event, mouse);

		if (singleplayer.B0getActive())
		{
			singleplayer.B0setActive(false);

			players.resetValues(); //set players' values to default

			//resets all values
			singleplayer.setText();
			singleplayer.setColors();
			singleplayer.S0setActive(false);
			singleplayer.setColorsInactive(false);

			//reset map
			mapreader.setSelectedmap(0); // read the first map
			singleplayer.M0setTiles(mapreader); //set new tiles
			singleplayer.setTransform();

			//goes back to main menu
			singleplayer.isActive = false;
			mainmenu.isActive = true;

			mainmenu.handleInput(event, mouse); //erases buggy output
		}
		else if (singleplayer.B1getActive())
		{
			singleplayer.B1setActive(false);
		}
		else if (singleplayer.TH0getChanged()) // if the text inside textholder has changed
		{
			settings.setName(singleplayer.TH0getString()); //set new name in settings
		}
		else if (players.relativecolors != singleplayer.S0getActive()) //if the state of relative colors has changed
		{
			players.relativecolors = singleplayer.S0getActive(); // set relative colors to new state

			if (players.relativecolors) // if state is true
			{
				players.setColorsTeamRelative(); //sets all colors relative to team
				singleplayer.setColorsInactive(true); //makes color dropdowns inactive
			}
			else // if state is false 
			{
				players.resetColors(); //resets colors back
				singleplayer.setColorsInactive(false); //makes color dropdowns active
			}
		}
		else if (singleplayer.M0getlActive())
		{
			mapreader.shiftSelectedmap(-1); // shift map backward
			singleplayer.M0setTiles(mapreader); //set new tiles
			singleplayer.setTransform();
			singleplayer.M0setlActive(false);
		}
		else if (singleplayer.M0getrActive())
		{
			mapreader.shiftSelectedmap(1); // shift map forward
			singleplayer.M0setTiles(mapreader); //set new tiles
			singleplayer.setTransform();
			singleplayer.M0setrActive(false);
		}

		for (short i = 1; i < 13; i++) //13 is the greatest number used in singleplayer dropdowns
		{
			if (i < 4 && singleplayer.D0getActive(i))
			{
				players.playerrace = i; //race changes to whatever it is equal to now
				singleplayer.D0setActive(i, false);
			}
			else if (i < 13 && singleplayer.D1getActive(i))
			{
				players.playerteam = i; // change team to new value

				if (players.relativecolors) //if relative colors is on
				{
					players.setPlayerColor(players.playerteam); //set color according to team
					singleplayer.setColors();
				}

				singleplayer.D1setActive(i, false);
			}
			else if (i < 13 && singleplayer.D2getActive(i))
			{
				players.setPlayerColor(i); //sets new player color
				singleplayer.setColors(); //displays changes
				singleplayer.D2setActive(i, false);
			}
			else if (i < players.ailimit + 1 && singleplayer.D3getActive(i))
			{
				players.setAiColorsAfter(players.ais); //set ai colors after the old ais number
				singleplayer.setColors(); //display them

				players.ais = i; //set new ais number

				singleplayer.D3setActive(i, false);
			}
			for (short j = 0; j < players.ais; j++)
			{
				if (i < 4 && singleplayer.D4getActive(j, i))
				{
					players.aidifficulty[j] = i; //sets new difficulty
					singleplayer.D4setActive(j, i, false);
				}
				else if (i < 4 && singleplayer.D5getActive(j, i))
				{
					players.airace[j] = i; //sets new race
					singleplayer.D5setActive(j, i, false);
				}
				else if (i < 11 && singleplayer.D6getActive(j, i))
				{
					players.aiteam[j] = i; //sets new team

					if (players.relativecolors) // if relative colors is on
					{
						players.setAiColor(j, players.aiteam[j]); //set color relative to team
						singleplayer.setColors(); //displays changes
					}

					singleplayer.D6setActive(j, i, false);
				}
				else if (i < 13 && singleplayer.D7getActive(j, i))
				{
					players.setAiColor(j, i);
					singleplayer.setColors(); //displays changes
					singleplayer.D7setActive(j, i, false);
				}
			}
		}
	}
	else if (multiplayer.isActive)
	{
		multiplayer.handleInput(event, mouse);

		if (multiplayer.B0getActive())
		{
			multiplayer.B0setActive(false);
			multiplayer.isActive = false;
			mainmenu.isActive = true;

			mainmenu.handleInput(event, mouse); //erases buggy output
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

			mainmenu.handleInput(event, mouse); //erases buggy output
		}
		else if (options.B1getActive()) //if "apply" is pressed
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
				//settings.setOldFullscreen(settings.getFullscreen()); //- dont know why this was used originally
				options.D1setActive(i, false);

				if (i == 1)
					settings.setFullscreen(true);
				else if (i == 2)
					settings.setFullscreen(false);
			}
			else if (i < 8 && options.D0getActive(i))
			{
				//settings.setOldRes(settings.getRes()); //- dont know why this was used originally
				options.D0setActive(i, false);
				sf::VideoMode mode = modes[i - 1];

				settings.setRes(sf::Vector2i(mode.width, mode.height));
			}
		}
	}
	else if (mainmenu.isActive)
	{
		mainmenu.handleInput(event, mouse);

		if (mainmenu.B0getActive()) //singleplayer
		{
			mainmenu.B0setActive(false);
			mainmenu.isActive = false;
			singleplayer.isActive = true;

			singleplayer.handleInput(event, mouse); //erases buggy output
		}
		else if (mainmenu.B1getActive()) //multiplayer
		{
			mainmenu.B1setActive(false);
			mainmenu.isActive = false;
			multiplayer.isActive = true;

			multiplayer.handleInput(event, mouse); //erases buggy output
		}
		else if (mainmenu.B2getActive()) //options
		{
			mainmenu.B2setActive(false);
			mainmenu.isActive = false;
			options.isActive = true;

			options.handleInput(event, mouse); //erases buggy output
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
	singleplayer.setColors();
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
	else if (singleplayer.isActive)
		window.draw(singleplayer);
	else if (multiplayer.isActive)
		window.draw(multiplayer);
	else if (options.isActive)
		window.draw(options);
	else if (mainmenu.isActive)
		window.draw(mainmenu);

	//draw cursor
	window.draw(cursor);
}
