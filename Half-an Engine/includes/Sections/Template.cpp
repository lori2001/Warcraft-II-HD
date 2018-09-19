#include "Template.h"

namespace Sections
{
	void Template::setTransform(const sf::Vector2f & size, const sf::Vector2f & scale)
	{
		this->scale = sf::Vector2f(size.x / (bsize.x - sizeofB.x * 2) * scale.x, size.y / (bsize.y - sizeofB.y * 2) * scale.y);

		border.setScale(this->scale);
		windowize.setScale(sf::Vector2f(this->scale.x / winprop.x, this->scale.x / winprop.y));

		windowize.setPosition(sf::Vector2f(windowize.getSize().x / 2 * windowize.getScale().x ,windowize.getSize().y / 2 * windowize.getScale().x));
	}
	void Template::handleInput(const sf::Event & event, const sf::Vector2f & mouse)
	{
		windowize.setSelected(mouse);
		windowize.handleInput(event, loading.pressbutton);
	}
	void Template::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		if(isWindowed)
			target.draw(border, states);

		if (windowize.getSelected())
			target.draw(windowize, states);
	}
}