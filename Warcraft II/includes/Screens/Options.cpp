#include "Options.h"

namespace Screens
{
	void Options::setTransform()
	{
		gears.setTopPosition(sf::Vector2f(float(settings.getRes().x) / 16, float(settings.getRes().y) / 14));
		gears.setBotPosition(sf::Vector2f(float(settings.getRes().x - settings.getRes().x / 16), float(settings.getRes().y - settings.getRes().y / 14)));
		back.setPosition(sf::Vector2f(float(settings.getRes().x / 4), float(settings.getRes().y / 1.25f)));
		apply.setPosition(sf::Vector2f(float(settings.getRes().x / 4 + apply.getBSize().x * 1.25f * settings.get1000Scale().x), float(settings.getRes().y / 1.25f)));

		backgroundS.setScale(settings.get1920Scale());
		gears.setTopScale(settings.get1920Scale());
		gears.setBotScale(settings.get1920Scale());
		back.setScale(settings.get1000Scale());
		apply.setScale(settings.get1000Scale());
	}
	void Options::handleInput(const sf::Event & event, const sf::Vector2f & mouse)
	{
		back.setSelected(mouse);
		apply.setSelected(mouse);

		back.handleInput(event, loading.pressbutton);
		apply.handleInput(event, loading.pressbutton);
	}
	void Options::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(backgroundS, states);
		target.draw(gears, states);
		target.draw(back, states);
		target.draw(apply, states);
	}
}