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

		music.setString("Music: " + std::to_string(settings.getMusic()));
		soundfx.setString("SoundFX: " + std::to_string(settings.getSoundFX()));
	}
	void Options::setTransform()
	{
		gears.setTopPosition(sf::Vector2f(float(1920) / 16, float(1080) / 14));
		gears.setBotPosition(sf::Vector2f(float(1920 - 1920 / 16), float(1080 - 1080 / 14)));
		back.setPosition(sf::Vector2f(float(1920 / 4), float(1080 / 1.25f)));
		apply.setPosition(sf::Vector2f(float(1920 / 4 + apply.getSize().x * 1.25f), float(1080 / 1.25f)));
		resolution.setPosition(sf::Vector2f(float(1920 / 2), float(1080 / 2)));
		fullscreen.setPosition(sf::Vector2f(float(1920 / 3.5f), float(1080 / 2)));
		music.setPosition(sf::Vector2f(float(1920 / 2.5f), float(1080 / 2.7f)));
		soundfx.setPosition(sf::Vector2f(float(1920 / 1.5f), float(1080 / 2.7f)));
	}
	void Options::handleInput(const sf::Event & event, const sf::Vector2f & mouse)
	{
		back.setSelected(mouse);
		apply.setSelected(mouse);
		resolution.setSelected(mouse);
		fullscreen.setSelected(mouse);
		music.setSelected(mouse);
		soundfx.setSelected(mouse);

		back.handleInput(event, loading.pressbutton);
		apply.handleInput(event, loading.pressbutton);
		resolution.handleInput(event, loading.pressbutton);
		fullscreen.handleInput(event, loading.pressbutton);
		music.handleInput(event, mouse, loading.pressbutton);
		soundfx.handleInput(event, mouse, loading.pressbutton);
	}
	void Options::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(backgroundS, states);
		target.draw(gears, states);
		target.draw(back, states);
		target.draw(apply, states);
		target.draw(resolution, states);
		target.draw(fullscreen, states);
		target.draw(music, states);
		target.draw(soundfx, states);
	}
}