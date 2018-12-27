#include "Multiplayer.h"

namespace Screens
{
	void Multiplayer::setTransform()
	{
		back.setPosition(sf::Vector2f(float((back.getSize().x / 2 + 15)), float(1080 - back.getSize().y)));
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