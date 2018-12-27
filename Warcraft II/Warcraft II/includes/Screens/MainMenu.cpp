#include "MainMenu.h"

namespace Screens
{
	void MainMenu::setTransform()
	{
		singleplayer.setPosition(sf::Vector2f(1920 / 2, float(1080 / 2 - 1.5f * singleplayer.getSize().y)));
		multiplayer.setPosition({1920/2, 1080/2});
		options.setPosition(sf::Vector2f(1920 / 2, float(1080 / 2 + 1.5f * options.getSize().y)));
		exit.setPosition(sf::Vector2f(1920 / 2, float(1080 / 2 + 3 * exit.getSize().y)));
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