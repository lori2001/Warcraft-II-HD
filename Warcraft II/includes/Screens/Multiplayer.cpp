#include "Multiplayer.h"

namespace Screens
{
	void Multiplayer::setTransform()
	{
		backgroundS.setScale(settings.get1920Scale());

		back.setPosition(sf::Vector2f(float((back.getSize().x / 2 + 15) * settings.get1920Scale().x), float(settings.getRes().y - back.getSize().y * settings.get1920Scale().y)));
		back.setScale(settings.get1920Scale());
	}
	void Multiplayer::handleInput(const sf::Event & event, const sf::Vector2f & mouse)
	{
		back.handleInput(event, loading.pressbutton);

		back.setSelected(mouse);
	}
	void Multiplayer::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		target.draw(backgroundS, states);
		target.draw(back, states);
	}
}