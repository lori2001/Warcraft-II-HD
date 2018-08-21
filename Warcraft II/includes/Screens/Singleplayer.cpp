#include "Singleplayer.h"

namespace Screens
{
	void Singleplayer::setTransform()
	{
		back.setScale(settings.get1000Scale());
		play.setScale(settings.get1000Scale());

		name.setScale(settings.get1000Scale());

		playerrace.setScale(settings.get1000Scale());
		playerteam.setScale(sf::Vector2f(settings.get1000Scale().x - (0.25f* settings.get1000Scale().x), settings.get1000Scale().y));
		playercolor.setScale(sf::Vector2f(settings.get1000Scale().x - (0.25f* settings.get1000Scale().x), settings.get1000Scale().y));

		ais.setScale(settings.get1000Scale());

		for (unsigned short i = 0; i < 11; i++)
		{
			aidifficulty[i].setScale(sf::Vector2f(0.85f * (settings.get1000Scale().x - (0.25f* settings.get1000Scale().x)), 0.85f * settings.get1000Scale().y));
			airace[i].setScale(sf::Vector2f(0.85f * (settings.get1000Scale().x - (0.25f* settings.get1000Scale().x)), 0.85f * settings.get1000Scale().y));
			aiteam[i].setScale(sf::Vector2f(0.85f * (settings.get1000Scale().x - (0.25f* settings.get1000Scale().x)), 0.85f * settings.get1000Scale().y));
			aicolor[i].setScale(sf::Vector2f(0.85f * (settings.get1000Scale().x - (0.25f* settings.get1000Scale().x)), 0.85f * settings.get1000Scale().y));
		}

		player.setCharacterSize(int(20 * settings.get1000Scale().y));

		relativecolors.setScale(settings.get1000Scale());

		mapselector.setScale(settings.get1920Scale());

		backgroundS.setScale(settings.get1920Scale());
		back.setPosition(sf::Vector2f(float((back.getSize().x / 2 + 15) * settings.get1000Scale().x), float(settings.getRes().y - back.getSize().y * settings.get1000Scale().y)));
		play.setPosition(sf::Vector2f(float(settings.getRes().x - (play.getSize().x * 1.75f + 15) * settings.get1000Scale().x), float(settings.getRes().y - play.getSize().y * settings.get1000Scale().y)));

		name.setPosition(sf::Vector2f(float((name.getSize().x / 2 + 30) * settings.get1000Scale().x), float(3 * name.getSize().y * settings.get1000Scale().y)));

		playerrace.setPosition(sf::Vector2f(float((name.getSize().x + 60 + playerrace.getSize().x / 2) * settings.get1000Scale().x), float(3 * name.getSize().y * settings.get1000Scale().y)));
		playerteam.setPosition(sf::Vector2f(float((name.getSize().x + 70 + playerteam.getSize().x * 1.5f) * settings.get1000Scale().x), float(3 * name.getSize().y * settings.get1000Scale().y)));
		playercolor.setPosition(sf::Vector2f(float((name.getSize().x + 80 + playercolor.getSize().x * 2.4f) * settings.get1000Scale().x), float(3 * name.getSize().y * settings.get1000Scale().y)));

		ais.setPosition(sf::Vector2f(float((ais.getSize().x / 2 + 15 * settings.get1000Scale().x)), float(5.8f * name.getSize().y * settings.get1000Scale().y)));

		for (unsigned short i = 0; i < 11; i++)
		{
			aidifficulty[i].setPosition(sf::Vector2f(float((name.getSize().x / 2 + 30) * settings.get1000Scale().x), float(5.8f * name.getSize().y * settings.get1000Scale().y + i * aidifficulty[i].getSize().y * settings.get1000Scale().y)));
			airace[i].setPosition(sf::Vector2f(float((name.getSize().x + 40) * settings.get1000Scale().x), float(5.8f * name.getSize().y * settings.get1000Scale().y + i * airace[i].getSize().y * settings.get1000Scale().y)));
			aiteam[i].setPosition(sf::Vector2f(float((name.getSize().x + 45 + 0.8f * aiteam[i].getSize().x) * settings.get1000Scale().x), float(5.8f * name.getSize().y * settings.get1000Scale().y + i * aiteam[i].getSize().y * settings.get1000Scale().y)));
			aicolor[i].setPosition(sf::Vector2f(float((name.getSize().x + 10 + aicolor[i].getSize().x * 1.9f) * settings.get1000Scale().x), float(5.8f * name.getSize().y * settings.get1000Scale().y + i * aicolor[i].getSize().y * settings.get1000Scale().y)));
		}

		player.setPosition(sf::Vector2f(float(player.getLocalBounds().width / 2 + 15 * settings.get1000Scale().x), float(back.getSize().y * settings.get1000Scale().y)));

		relativecolors.setPosition(sf::Vector2f(float(3 * relativecolors.getSSize().x * settings.get1000Scale().x), float(16 * relativecolors.getSSize().x * settings.get1000Scale().y)));
	
		mapselector.setPosition(sf::Vector2f(1650 * mapselector.getScale().x, 175 * mapselector.getScale().y));
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
		for (short i = 1; i <= 12; i++) //starts from 1 because we want the numbers to be right
			playerteam.setDroptext(i, "Team " + std::to_string(i));
		playerteam.setDroptext(0, playerteam.getDroptext(players.playerteam));

		//set aiumber's dropdown texts
		ais.setMaintext("AI: ");
		for (short i = 1; i <= 11; i++)
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
		for (short i = 0; i < 12; i++)
		{
			playercolor.setDropColor(i + 1, colors[i]);
		}
		playercolor.setDropColor(0, playercolor.getDropColor(players.playercolor));

		//sets ais'colors
		for (short i = 0; i < 11; i++)
		{
			for (short j = 0; j < 12; j++)
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