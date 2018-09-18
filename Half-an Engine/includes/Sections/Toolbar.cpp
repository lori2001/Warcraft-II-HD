#include "Toolbar.h"

namespace Sections
{
	void Toolbar::setTransform(const sf::Vector2f & scale)
	{
		dropdown1.setDroptext(0, "Fullscreen");
		dropdown1.setDroptext(1, "On");
		dropdown1.setDroptext(2, "Off");

		Template::setTransform(this->size, scale);

		dropdown1.setScale(scale);
		dropdown2.setScale(scale);
		dropdown3.setScale(scale);
		dropdown4.setScale(scale);

		dropdown1.setPosition(sf::Vector2f(dropdown1.getSize().x * 0.5f * scale.x, dropdown1.getSize().y * 0.5f * scale.y));
		dropdown2.setPosition(sf::Vector2f(dropdown2.getSize().x * 1.5f * scale.x, dropdown2.getSize().y * 0.5f * scale.y));
		dropdown3.setPosition(sf::Vector2f(dropdown3.getSize().x * 2.5f * scale.x, dropdown3.getSize().y * 0.5f * scale.y));
		dropdown4.setPosition(sf::Vector2f(dropdown4.getSize().x * 3.5f * scale.x, dropdown4.getSize().y * 0.5f * scale.y));

		//ist an ugly way of forcing the window to the proper size
		windowsize = sf::Vector2f{ size.x + 2 * Template::sizeofB.x * Template::scale.x / scale.x, size.y + 2 * Template::sizeofB.y * Template::scale.y / scale.y };
	}
	void Toolbar::windowize(const sf::Vector2f & scale)
	{
		Template::isWindowed = true;

		dropdown1.setPosition(sf::Vector2f(dropdown1.getSize().x * 0.5f * scale.x + Template::sizeofB.x * Template::scale.x, dropdown1.getSize().y * 0.5f * scale.y + Template::sizeofB.y * Template::scale.y));
		dropdown2.setPosition(sf::Vector2f(dropdown2.getSize().x * 1.5f * scale.x + Template::sizeofB.x * Template::scale.x, dropdown2.getSize().y * 0.5f * scale.y + Template::sizeofB.y * Template::scale.y));
		dropdown3.setPosition(sf::Vector2f(dropdown3.getSize().x * 2.5f * scale.x + Template::sizeofB.x * Template::scale.x, dropdown3.getSize().y * 0.5f * scale.y + Template::sizeofB.y * Template::scale.y));
		dropdown4.setPosition(sf::Vector2f(dropdown4.getSize().x * 3.5f * scale.x + Template::sizeofB.x * Template::scale.x, dropdown4.getSize().y * 0.5f * scale.y + Template::sizeofB.y * Template::scale.y));
	}
	void Toolbar::unwindowize(const sf::Vector2f & scale)
	{
		Template::isWindowed = false;

		dropdown1.setPosition(sf::Vector2f(dropdown1.getSize().x * 0.5f * scale.x, dropdown1.getSize().y * 0.5f * scale.y));
		dropdown2.setPosition(sf::Vector2f(dropdown2.getSize().x * 1.5f * scale.x, dropdown2.getSize().y * 0.5f * scale.y));
		dropdown3.setPosition(sf::Vector2f(dropdown3.getSize().x * 2.5f * scale.x, dropdown3.getSize().y * 0.5f * scale.y));
		dropdown4.setPosition(sf::Vector2f(dropdown4.getSize().x * 3.5f * scale.x, dropdown4.getSize().y * 0.5f * scale.y));
	}
	void Toolbar::handleInput(const sf::Event & event, const sf::Vector2f & mouse)
	{
		Template::handleInput(event, mouse);

		if (!Template::windowize.getSelected())
		{
			dropdown1.setSelected(mouse);
			dropdown1.handleInput(event, loading.pressbutton);
			dropdown2.setSelected(mouse);
			dropdown2.handleInput(event, loading.pressbutton);
			dropdown3.setSelected(mouse);
			dropdown3.handleInput(event, loading.pressbutton);
			dropdown4.setSelected(mouse);
			dropdown4.handleInput(event, loading.pressbutton);
		}
	}
	void Toolbar::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(dropdown1, states);
		target.draw(dropdown2, states);
		target.draw(dropdown3, states);
		target.draw(dropdown4, states);

		Template::draw(target, states);
	}
}