#pragma once
#include "SFML/Graphics.hpp"
#include "../UI/Button.h"
#include "../RW/Loading.h"

namespace Sections
{
	class Template
	{
	protected:
		RW::Loading loading;

		sf::Vector2f winprop{ sf::Vector2f(1,1)}; // makes window scaling easily changeable
		UI::Button windowize{ sf::Vector2f(125, 125) };

		sf::Vector2f bsize{ 1920,1080 }; // size of intial border sprite
		sf::Vector2f sizeofB{ 34,44 }; // size of the actual border in the file in pixels
		sf::Vector2f scale{1,1}; // holds the number used as scale, defaults to 1/1
		sf::RectangleShape border{ bsize }; //border sprite

		bool isWindowed = false;
	public:
		Template() 
		{
			windowize.setTexture(loading.undockT);
			windowize.setSelectColor(sf::Color::Transparent);

			border.setTexture(&loading.borderT);
		}

		Window window;

		void setTransform(const sf::Vector2f & size, const sf::Vector2f & scale);
		void handleInput(const sf::Event &event, const sf::Vector2f & mouse);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	};
}