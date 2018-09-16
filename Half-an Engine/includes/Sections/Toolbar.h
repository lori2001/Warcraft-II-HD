#pragma once
#include "SFML\Graphics.hpp"
#include "..\Window.h"
#include "..\UI\Dropdown.h"
#include "..\RW\Loading.h"

namespace Sections
{
	class Toolbar : public sf::Drawable
	{
	private:
		RW::Loading loading;

		UI::Dropdown dropdown1{ 3 , true};
		UI::Dropdown dropdown2{ 2 , true };
		UI::Dropdown dropdown3{ 3 , true };
		UI::Dropdown dropdown4{ 3 , true };

		sf::Vector2f size{ dropdown1.getSize().x * 4, dropdown1.getSize().y * 3 };
	public:
		Toolbar()
		{
			dropdown1.setTexture(loading.dropdownT, loading.warcraftF);
			dropdown2.setTexture(loading.dropdownT, loading.warcraftF);
			dropdown3.setTexture(loading.dropdownT, loading.warcraftF);
			dropdown4.setTexture(loading.dropdownT, loading.warcraftF);
		}
		bool isWindowed = false;
		Window window;

		void setTransform(const sf::Vector2f & scale);
		void handleInput(const sf::Event &event, const sf::Vector2f & mouse);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		//getters
		sf::Vector2f getSize() { return size; }
	};
}