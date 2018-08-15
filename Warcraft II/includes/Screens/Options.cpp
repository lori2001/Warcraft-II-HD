#include "Options.h"

namespace Screens
{
	void Options::setText(const std::vector<sf::VideoMode>& modes)
	{
		resolution.setMaintext("Resolution");
		resolution.setDroptext(0, std::to_string(settings.getRes().x) + "x" + std::to_string(settings.getRes().y));

		for (unsigned i = 1; i < resolution.getElementnr(); i++)
		{
			if (i <= modes.size())
			{
				sf::VideoMode mode = modes[i - 1];
				resolution.setDroptext(i, std::to_string(mode.width) + "x" + std::to_string(mode.height));
			}
		}

		fullscreen.setMaintext("Fullscreen");

		if (settings.getFullscreen())
			fullscreen.setDroptext(0, "On");
		else
			fullscreen.setDroptext(0, "Off");

		fullscreen.setDroptext(1, "On");
		fullscreen.setDroptext(2, "Off");
	}
	void Options::setTransform()
	{
		gears.setTopPosition(sf::Vector2f(float(settings.getRes().x) / 16, float(settings.getRes().y) / 14));
		gears.setBotPosition(sf::Vector2f(float(settings.getRes().x - settings.getRes().x / 16), float(settings.getRes().y - settings.getRes().y / 14)));
		back.setPosition(sf::Vector2f(float(settings.getRes().x / 4), float(settings.getRes().y / 1.25f)));
		apply.setPosition(sf::Vector2f(float(settings.getRes().x / 4 + apply.getBSize().x * 1.25f * settings.get1000Scale().x), float(settings.getRes().y / 1.25f)));
		resolution.setPosition(sf::Vector2f(float(settings.getRes().x / 2), float(settings.getRes().y / 2)));
		fullscreen.setPosition(sf::Vector2f(float(settings.getRes().x / 3.5f), float(settings.getRes().y / 2)));

		backgroundS.setScale(settings.get1920Scale());
		gears.setTopScale(settings.get1920Scale());
		gears.setBotScale(settings.get1920Scale());
		back.setScale(settings.get1000Scale());
		apply.setScale(settings.get1000Scale());
		resolution.setScale(settings.get1000Scale());
		fullscreen.setScale(settings.get1000Scale());
	}
	void Options::handleInput(const sf::Event & event, const sf::Vector2f & mouse)
	{
		back.setSelected(mouse);
		apply.setSelected(mouse);
		resolution.setSelected(mouse);
		fullscreen.setSelected(mouse);

		back.handleInput(event, loading.pressbutton);
		apply.handleInput(event, loading.pressbutton);
		resolution.handleInput(event, loading.pressbutton);
		fullscreen.handleInput(event, loading.pressbutton);
	}
	void Options::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(backgroundS, states);
		target.draw(gears, states);
		target.draw(back, states);
		target.draw(apply, states);
		target.draw(resolution, states);
		target.draw(fullscreen, states);
	}
}