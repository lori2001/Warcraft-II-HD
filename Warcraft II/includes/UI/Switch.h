#pragma once
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"

namespace UI
{
	class Switch : public sf::Drawable
	{
	private:
		const sf::Vector2f *boxsize; // outlines size
		const sf::Vector2f *rsize = new const sf::Vector2f{ 25,28 }; // rectangles size (this is general bc its needed when settings texture coords for circle)
		sf::RectangleShape * rect; // rectangle object
		sf::RectangleShape * rectOutline; //outline

		const float *csize; // circles size
		sf::CircleShape * circle; //circle object

		sf::Text *text = new sf::Text; // a text to be next to the button

		bool *isPressed = new bool{ false };
		bool *isSelected = new bool{ false };
		bool *isActive = new bool{ false };

		unsigned short *type = new unsigned short; // 2 types 0-rectangle 1-circle
	public:
		Switch(const unsigned short & type)
		{
			if (type == 0)
			{
				//sets scales to objects to be made
				boxsize = new const sf::Vector2f{ 21,21 };

				//creates the proper objects
				rect = new sf::RectangleShape{ *rsize };
				rectOutline = new sf::RectangleShape{ *boxsize };

				//set default attributes
				rect->setOrigin(sf::Vector2f(this->rsize->x / 2, this->rsize->y / 2));
				rectOutline->setOutlineColor(sf::Color::Yellow);
				rectOutline->setOutlineThickness(-1);
				rectOutline->setFillColor(sf::Color::Transparent);
				rectOutline->setOrigin(sf::Vector2f(boxsize->x - boxsize->x * 2 / 5, boxsize->y - boxsize->y * 5 / 13));
			}
			else
			{
				//sets circle size
				csize = new const float{ 20 };

				//creates circle
				circle = new sf::CircleShape{ *csize / 2 };

				//set default attributes
				circle->setOrigin(sf::Vector2f(*this->csize / 2, *this->csize / 2));
				circle->setOutlineColor(sf::Color::Yellow);
			}
			text->setFillColor(sf::Color::Black);

			*this->type = type;
		}
		Switch() : Switch(0) {} // as default constructor use the rect type
		Switch(const unsigned short & type, const std::string &text) : Switch(type)
		{
			this->text->setString(text);
		}
		Switch(const std::string &text) : Switch(0, text) {} // constructor which defaults to rect type and takes in text
		~Switch()
		{
			//deletes only objects specific to type
			if (*type == 0)
			{
				delete boxsize;
				delete rect;
				delete rectOutline;
			}
			else
			{
				delete csize;
				delete circle;
			}

			//deletes general objects
			delete rsize;
			delete text;
			delete isPressed;
			delete isSelected;
			delete isActive;
			delete type;
		}
		void setSelected(const sf::Vector2f & mouse);
		void handleInput(const sf::Event &event, sf::Sound & pressbutton);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		//setters
		void setTexture(const sf::Texture & texture, const sf::Font &font);
		void setPosition(const sf::Vector2f &position);
		void setScale(const sf::Vector2f &scale);
		void setText(const std::string &text);

		//getters
		sf::Vector2f getSSize() const
		{
			if (*type == 0)
				return *rsize;
			else
				return sf::Vector2f(*csize, *csize);
		}
		bool getActive() const { return *isActive; }
	};
}