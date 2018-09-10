#pragma once
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"

namespace UI
{
	class Switch : public sf::Drawable
	{
	private:
		const sf::Vector2f boxsize{ 40,40 }; // outlines size
		const sf::Vector2f rsize{ 48,50 }; // rectangles size (this is general bc its needed when settings texture coords for circle)
		sf::RectangleShape rect{ rsize }; // rectangle object
		sf::RectangleShape rectOutline{ boxsize }; //outline

		const float csize = 36; // circles size
		sf::CircleShape circle{ csize / 2 };; //circle object

		sf::Text text; // a text to be next to the button

		bool isPressed = false;
		bool isSelected = false;
		bool isActive = false;

		bool isCircle = false; // types: false-rectangle true-circle
	public:
		Switch(const unsigned short & isCircle)
		{
			//set specific attributes
			if (isCircle)
			{
				circle.setOrigin(sf::Vector2f(this->csize / 2, this->csize / 2));
				circle.setOutlineColor(sf::Color::Yellow);
			}
			else
			{
				rect.setOrigin(sf::Vector2f(this->rsize.x / 2, this->rsize.y / 2));
				rectOutline.setOutlineColor(sf::Color::Yellow);
				rectOutline.setOutlineThickness(-1);
				rectOutline.setFillColor(sf::Color::Transparent);
				rectOutline.setOrigin(sf::Vector2f(boxsize.x - boxsize.x * 2 / 5, boxsize.y - boxsize.y * 5 / 13));
			}

			//set common attributes
			text.setFillColor(sf::Color::Black);
			this->isCircle = isCircle;
		}
		Switch() : Switch(0) {} // as default constructor use the rect type
		Switch(const unsigned short & type, const std::string &text) : Switch(type)
		{
			this->text.setString(text);
		}
		Switch(const std::string &text) : Switch(0, text) {} // constructor which defaults to rect type and takes in text

		void setSelected(const sf::Vector2f & mouse);
		void handleInput(const sf::Event &event, sf::Sound & pressbutton);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		//setters
		void setTexture(const sf::Texture & texture, const sf::Font &font);
		void setPosition(const sf::Vector2f &position);
		void setScale(const sf::Vector2f &scale);
		void setText(const std::string &text);
		void setActive(const bool &isActive) { this->isActive = isActive; }

		//getters
		sf::Vector2f getSSize() const
		{
			if (isCircle)
				return sf::Vector2f(csize, csize);
			else
				return rsize;
		}
		bool getActive() const { return isActive; }
	};
}