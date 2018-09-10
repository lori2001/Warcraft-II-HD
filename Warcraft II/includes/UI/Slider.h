#pragma once
#include <assert.h>
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"

namespace UI
{
	class Slider : public sf::Drawable
	{
	private:
		const sf::Vector2f ssize { 407,45 }; // slider size
		const sf::Vector2f csize { 335,31 }; // center body size
		const sf::Vector2f lrsize { 33,31 }; // left and right arrow size
		const sf::Vector2f center { 407 / 2,31 / 2 }; // the center of the whole slider
		const sf::Vector2f bsize { 33,27 }; // the size of the button

		sf::RectangleShape slider { ssize };
		sf::RectangleShape button { bsize };

		//these are shown if selected
		sf::RectangleShape centerOutline { csize };
		sf::RectangleShape leftOutline { lrsize };
		sf::RectangleShape rightOutline { lrsize };

		bool isPressed = false; //true if left mouse button is pressed while it is selected
		bool iscSelected = false; //true if the center is selected
		bool isrSelected = false; // true if right arrow is selected
		bool islSelected = false; // true if left arrow is selected
		bool isActive = false; //true if level changes

		unsigned short level = 5; //contains slider position - defaults to rthe center

		sf::Text text; // text above slider
	public:
		Slider()
		{
			//sets all origins to center
			slider.setOrigin(center);
			button.setOrigin(sf::Vector2f(bsize.x / 2, bsize.y / 2));
			centerOutline.setOrigin(sf::Vector2f(csize.x / 2, csize.y / 2));
			leftOutline.setOrigin(sf::Vector2f(lrsize.x / 2, lrsize.y / 2));
			rightOutline.setOrigin(sf::Vector2f(lrsize.x / 2, lrsize.y / 2));

			/*makes rectangles look like outlines*/
			centerOutline.setOutlineColor(sf::Color::Yellow);
			leftOutline.setOutlineColor(sf::Color::Yellow);
			rightOutline.setOutlineColor(sf::Color::Yellow);

			centerOutline.setOutlineThickness(-2);
			leftOutline.setOutlineThickness(-2);
			rightOutline.setOutlineThickness(-2);

			centerOutline.setFillColor(sf::Color::Transparent);
			leftOutline.setFillColor(sf::Color::Transparent);
			rightOutline.setFillColor(sf::Color::Transparent);
			/*************************************/

			//makes text yellow by default
			text.setFillColor(sf::Color::Yellow);
		}
		Slider(const std::string txt) : Slider()
		{
			text.setString(txt);
		}

		void setSelected(const sf::Vector2f & mouse);
		void handleInput(const sf::Event &event, const sf::Vector2f & mouse, sf::Sound & pressbutton);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		//setters
		void setTexture(const sf::Texture &sliderT, const sf::Texture &buttonT, const sf::Font & font);
		void setPosition(const sf::Vector2f &position);
		void setSelectColor(const sf::Color &color);
		void setScale(const sf::Vector2f &scale);
		void setString(const std::string & txt);
		void setActive(const bool & active);
		void setLevel(const unsigned short  & lvl);

		//getters
		bool getActive() const { return isActive; }
		unsigned short getLevel() const { return level; }
	};
}