#include "Singleplayer.h"

namespace Screens
{
	void Singleplayer::setTransform()
	{
		playerteam.setScale({ 0.75f, 1 });
		playercolor.setScale({ 0.75f, 1 });

		for (int i = 0; i < 11; i++)
		{
			aidifficulty[i].setScale({ 0.65f, 0.85f });
			airace[i].setScale({ 0.65f, 0.85f });
			aiteam[i].setScale({ 0.65f, 0.85f });
			aicolor[i].setScale({0.65f, 0.85f});
		}

		player.setCharacterSize(38);

		back.setPosition({ 320, 990 });
		play.setPosition(sf::Vector2f(800, 990));
		name.setPosition(sf::Vector2f(240, 108));

		playerrace.setPosition(sf::Vector2f(name.getPosition().x + 368, name.getPosition().y));
		playerteam.setPosition(sf::Vector2f(playerrace.getPosition().x + 288, name.getPosition().y));
		playercolor.setPosition(sf::Vector2f(playerteam.getPosition().x + 256, name.getPosition().y));

		ais.setPosition(sf::Vector2f(80, 216));

		for (int i = 0; i < 11; i++)
		{
			aidifficulty[i].setPosition(sf::Vector2f(ais.getPosition().x + 160, 216 + (i * aidifficulty[i].getSize().y)));
			airace[i].setPosition(sf::Vector2f(aidifficulty[i].getPosition().x + 208, 216 + (i * airace[i].getSize().y)));
			aiteam[i].setPosition(sf::Vector2f(airace[i].getPosition().x + 208, 216 + (i * aiteam[i].getSize().y)));
			aicolor[i].setPosition(sf::Vector2f(aiteam[i].getPosition().x + 208, 216 + (i * aicolor[i].getSize().y)));
		}

		player.setPosition(sf::Vector2f(64, 27));
		
		relativecolors.setPosition(sf::Vector2f(160, 810));

		mapselector.setPosition(sf::Vector2f(1650, 175));
	}
	void Singleplayer::handleInput(const sf::Event & event, const sf::Vector2f & mouse)
	{
		back.setSelected(mouse);
		play.setSelected(mouse);

		name.setSelected(mouse);

		playerrace.setSelected(mouse);
		playerteam.setSelected(mouse);
		playercolor.setSelected(mouse);

		ais.setSelected(mouse);

		if (!playerrace.getDroppeddown() && !playerteam.getDroppeddown() && !playercolor.getDroppeddown())
		{
			aidifficulty[0].setSelected(mouse);
			airace[0].setSelected(mouse);
			aiteam[0].setSelected(mouse);
			aicolor[0].setSelected(mouse);

			for (int i = 0; i < std::stoi(ais.getDroptext(0)); i++)
			{
				bool isNotRestricted = true;
				for (int j = 0; j < i; j++)
				{
					if (aidifficulty[j].getDroppeddown() || airace[j].getDroppeddown() || aiteam[j].getDroppeddown() || aicolor[j].getDroppeddown())
					{
						isNotRestricted = false;
						break;
					}
				}

				if (isNotRestricted)
				{
					aidifficulty[i].setSelected(mouse);
					airace[i].setSelected(mouse);
					aiteam[i].setSelected(mouse);
					aicolor[i].setSelected(mouse);
				}
			}
		}

		relativecolors.setSelected(mouse);

		mapselector.setSelected(mouse);

		back.handleInput(event, loading.pressbutton);
		play.handleInput(event, loading.pressbutton);

		name.handleInput(event, loading.pressbutton);

		playerrace.handleInput(event, loading.pressbutton);
		playerteam.handleInput(event, loading.pressbutton);
		playercolor.handleInput(event, loading.pressbutton);

		ais.handleInput(event, loading.pressbutton);

		for (int i = 0; i < std::stoi(ais.getDroptext(0)); i++)
		{
			aidifficulty[i].handleInput(event, loading.pressbutton);
			airace[i].handleInput(event, loading.pressbutton);
			aiteam[i].handleInput(event, loading.pressbutton);
			aicolor[i].handleInput(event, loading.pressbutton);
		}

		relativecolors.handleInput(event, loading.pressbutton);

		mapselector.handleInput(event, loading.pressbutton);
	}
	void Singleplayer::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		target.draw(backgroundS, states);

		target.draw(back, states);
		target.draw(play, states);
		target.draw(relativecolors, states);

		for (int i = std::stoi(ais.getDroptext(0)) - 1; i >= 0; i--) //draws things backwards so first things come on top
		{
			target.draw(aidifficulty[i], states);
			target.draw(airace[i], states);
			target.draw(aiteam[i], states);
			target.draw(aicolor[i], states);
		}

		target.draw(ais, states);

		target.draw(playerrace, states);
		target.draw(playerteam, states);
		target.draw(playercolor, states);

		target.draw(name, states);
		target.draw(player, states);
		target.draw(mapselector, states);
	}
	void Singleplayer::setText()
	{
		//set player's race dropdown texts
		playerrace.setDroptext(1, "Random");
		playerrace.setDroptext(2, "Orcs[");
		playerrace.setDroptextColor(2, sf::Color::Red);
		playerrace.setDroptext(3, "Humans]");
		playerrace.setDroptextColor(3, sf::Color::Blue);
		playerrace.setDroptext(0, playerrace.getDroptext(players.playerrace));

		//set player's teams dropdown texts
		for (int i = 1; i <= 12; i++) //starts from 1 because we want the numbers to be right
			playerteam.setDroptext(i, "Team " + std::to_string(i));
		playerteam.setDroptext(0, playerteam.getDroptext(players.playerteam));

		//set aiumber's dropdown texts
		ais.setMaintext("AI: ");
		for (int i = 1; i <= 11; i++)
			ais.setDroptext(i, std::to_string(i));
		ais.setDroptext(0, ais.getDroptext(players.ais));

		for (int i = 0; i < 11; i++) // for every ai
		{
			//set ai difficulty's dropdown texts
			aidifficulty[i].setDroptext(1, "Easy");
			aidifficulty[i].setDroptext(2, "Medium");
			aidifficulty[i].setDroptext(3, "Hard");
			aidifficulty[i].setDroptext(0, aidifficulty[i].getDroptext(players.aidifficulty[i]));

			//set ai airace's dropdown texts
			airace[i].setDroptext(1, "Random");
			airace[i].setDroptext(2, "Orcs[");
			airace[i].setDroptextColor(2, sf::Color::Red);
			airace[i].setDroptext(3, "Humans]");
			airace[i].setDroptextColor(3, sf::Color::Blue);
			airace[i].setDroptext(0, airace[i].getDroptext(players.airace[i]));

			//set ai aiteam's dropdown texts
			for (int j = 1; j < 13; j++)
				aiteam[i].setDroptext(j, "Team " + std::to_string(j));
			aiteam[i].setDroptext(0, aiteam[i].getDroptext(players.aiteam[i]));
		}
	}
	void Singleplayer::setColors()
	{
		//sets player's colors
		for (int i = 0; i < 12; i++)
		{
			playercolor.setDropColor(i + 1, colors[i]);
		}
		playercolor.setDropColor(0, playercolor.getDropColor(players.playercolor));

		//sets ais'colors
		for (int i = 0; i < 11; i++)
		{
			for (int j = 0; j < 12; j++)
			{
				aicolor[i].setDropColor(j + 1, colors[j]);
			}
			aicolor[i].setDropColor(0, aicolor[i].getDropColor(players.aicolor[i]));
		}
	}
	void Singleplayer::setColorsInactive(const bool &inactive)
	{
		playercolor.setInactive(inactive);

		for (int i = 0; i < 11; i++)
		{
			aicolor[i].setInactive(inactive);
		}
	}
}