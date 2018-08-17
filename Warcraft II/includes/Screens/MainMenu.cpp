#include "MainMenu.h"

namespace Screens
{
	void MainMenu::setTransform()
	{
		backgroundS.setScale(settings.get1920Scale());
		singleplayer.setScale(settings.get1000Scale());
		multiplayer.setScale(settings.get1000Scale());
		options.setScale(settings.get1000Scale());
		exit.setScale(settings.get1000Scale());

		singleplayer.setPosition(sf::Vector2f(float(settings.getRes().x / 2), float(settings.getRes().y / 2 - 1.5f * singleplayer.getSize().y * settings.get1000Scale().y)));
		multiplayer.setPosition(sf::Vector2f(settings.getRes() / 2));
		options.setPosition(sf::Vector2f(float(settings.getRes().x / 2), float(settings.getRes().y / 2 + 1.5f * options.getSize().y * settings.get1000Scale().y)));
		exit.setPosition(sf::Vector2f(float(settings.getRes().x / 2), float(settings.getRes().y / 2 + 3 * exit.getSize().y * settings.get1000Scale().y)));
	}
	void MainMenu::handleInput(const sf::Event & event, const sf::Vector2f & mouse)
	{
		singleplayer.setSelected(mouse);
		multiplayer.setSelected(mouse);
		options.setSelected(mouse);
		exit.setSelected(mouse);

		singleplayer.handleInput(event, loading.pressbutton);
		multiplayer.handleInput(event, loading.pressbutton);
		options.handleInput(event, loading.pressbutton);
		exit.handleInput(event, loading.pressbutton);
	}
	void MainMenu::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		target.draw(backgroundS, states);
		target.draw(singleplayer, states);
		target.draw(multiplayer, states);
		target.draw(options, states);
		target.draw(exit, states);
	}
}