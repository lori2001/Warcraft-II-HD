#include "Toolbar.h"

namespace Sections
{
	void Toolbar::setTransform(const sf::Vector2f & scale)
	{
		dropfile.setDroptext(0, "File");
		dropfile.setDroptext(1, "New");
		dropfile.setDroptext(2, "Open");
		dropfile.setDroptext(3, "Save");
		dropfile.setDroptext(4, "Save as");

		dropwindow.setDroptext(0, "Window");
		dropwindow.setDroptext(1, "Unit Editor");
		dropwindow.setDroptext(2, "Map Editor");
		dropwindow.setDroptext(3, "Animations");
		dropwindow.setDroptext(4, "Text Editor");

		Template::setTransform(this->size, scale);

		background.setScale(scale);
		dropfile.setScale(scale);
		dropwindow.setScale(scale);

		dropfile.setPosition(sf::Vector2f(dropfile.getSize().x * 0.5f * scale.x, dropfile.getSize().y * 0.5f * scale.y));
		dropwindow.setPosition(sf::Vector2f(dropwindow.getSize().x * 1.5f * scale.x, dropwindow.getSize().y * 0.5f * scale.y));

		//ist an ugly way of forcing the window to the proper size
		windowsize = sf::Vector2f{ size.x + 2 * Template::sizeofB.x * Template::scale.x / scale.x, size.y + 2 * Template::sizeofB.y * Template::scale.y / scale.y };
	}
	void Toolbar::windowize(const sf::Vector2f & scale)
	{
		Template::isWindowed = true;

		background.setPosition(sf::Vector2f(Template::sizeofB.x * Template::scale.x, Template::sizeofB.y * Template::scale.y));
		dropfile.setPosition(sf::Vector2f(dropfile.getSize().x * 0.5f * scale.x + Template::sizeofB.x * Template::scale.x, dropfile.getSize().y * 0.5f * scale.y + Template::sizeofB.y * Template::scale.y));
		dropwindow.setPosition(sf::Vector2f(dropwindow.getSize().x * 1.5f * scale.x + Template::sizeofB.x * Template::scale.x, dropwindow.getSize().y * 0.5f * scale.y + Template::sizeofB.y * Template::scale.y));
	}
	void Toolbar::unwindowize(const sf::Vector2f & scale)
	{
		Template::isWindowed = false;

		background.setPosition(sf::Vector2f(0,0));
		dropfile.setPosition(sf::Vector2f(dropfile.getSize().x * 0.5f * scale.x, dropfile.getSize().y * 0.5f * scale.y));
		dropwindow.setPosition(sf::Vector2f(dropwindow.getSize().x * 1.5f * scale.x, dropwindow.getSize().y * 0.5f * scale.y));
	}
	void Toolbar::handleInput(const sf::Event & event, const sf::Vector2f & mouse)
	{
		Template::handleInput(event, mouse);

		if (!Template::windowize.getSelected())
		{
			dropfile.setSelected(mouse);
			dropfile.handleInput(event, loading.pressbutton);
			dropwindow.setSelected(mouse);
			dropwindow.handleInput(event, loading.pressbutton);
		}
	}
	void Toolbar::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(background, states);
		target.draw(dropfile, states);
		target.draw(dropwindow, states);

		Template::draw(target, states);
	}
}