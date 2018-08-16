#include "Multiplayer.h"

namespace Screens
{
	void Multiplayer::setTransform()
	{
		backgroundS.setScale(settings.get1920Scale());

		back.setPosition(sf::Vector2f(float((back.getBSize().x / 2 + 15) * settings.get1000Scale().x), float(settings.getRes().y - back.getBSize().y * settings.get1000Scale().y)));
		back.setScale(settings.get1000Scale());
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