#pragma once
#include "SFML/Graphics.hpp"
#include "..\Window.h"
#include "..\UI\Dropdown.h"
#include "..\RW\Loading.h"
#include "Template.h"

namespace Sections
{
	class Toolbar : public sf::Drawable, public Template
	{
	private:
		RW::Loading loading;

		UI::Dropdown dropfile{ 4 , true};
		UI::Dropdown dropwindow{ 5 , true };

		//total size of buttons
		sf::Vector2f size{ dropfile.getSize().x * 2, dropfile.getSize().y * 5};
		//(HD only/ needs scaling) size of buttons + size of border (2 times for both sides)
		sf::Vector2f windowsize{size.x + 2 * Template::sizeofB.x, size.y + 2 * Template::sizeofB.y};
	public:
		Toolbar()
		{
			dropfile.setTexture(loading.dropdownT, loading.warcraftF);
			dropwindow.setTexture(loading.dropdownT, loading.warcraftF);
		}

		void setTransform(const sf::Vector2f & scale);
		void windowize(const sf::Vector2f & scale);
		void unwindowize(const sf::Vector2f & scale);
		void handleInput(const sf::Event &event, const sf::Vector2f & mouse);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		//setters
		void B0setActive(const bool &active) { Template::windowize.setActive(active); }

		//getters
		bool getWindowed() { return Template::isWindowed; }
		bool B0getActive() { return Template::windowize.getActive(); }
		sf::Vector2f getSize() { return size; }
		sf::Vector2f getWindowSize() { return windowsize; }
	};
}