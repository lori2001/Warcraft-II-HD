#pragma once
#include <assert.h>
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"

namespace UI
{
	class Dropdown : public sf::Drawable
	{
	private:
		sf::Vector2f *size = new sf::Vector2f{ 277,40 }; // the size of a closed dropdown

		sf::RectangleShape *sprite = new sf::RectangleShape{ *size };
		sf::RectangleShape *selectedsprite = new sf::RectangleShape{ *size }; //holds the outline for selected dropdown parts

		bool *isPressed = new bool{ false }; // if true do the the pressed animation and play the sound(once)
		bool *isSelected = new bool{ false }; // if true show outline
		bool *isDroppeddown = new bool{ false }; // if true drop down
		bool *isActive; // if true react(ex. change 800x600 resolution to 1000x600) - this is done in Menu.cpp
		bool *isInactive = new bool{ false }; // if true make it grey and set it to unselectable

		unsigned short *elementnr = new unsigned short; // holds the number of elements in the dropdown
		bool *elementselected; // array of size elementnr | if a member is true it is selected | else not

		sf::Text * maintext; // text above dropdown
		sf::Text * droptext; // text in dropdown
		sf::RectangleShape * dropcolor; // used only if you want colors instead of texts
	public:
		Dropdown(const unsigned short &elementnr)
		{
			*this->elementnr = elementnr;

			maintext = new sf::Text;
			droptext = new sf::Text[elementnr];
			dropcolor = new sf::RectangleShape[elementnr];

			elementselected = new bool[elementnr] { false };
			isActive = new bool[elementnr] { false };

			maintext->setFillColor(sf::Color::Yellow);

			for (unsigned short i = 0; i < elementnr; i++)
			{
				droptext[i].setFillColor(sf::Color::Yellow); // set text color

				dropcolor[i].setSize(sf::Vector2f(size->x * 0.9652f, size->y * 0.8181f)); // a bit smaller than the whole dropdown
				dropcolor[i].setOrigin(sf::Vector2f(float((size->x * 0.9652f) / 2), float((size->y * 0.8181f) / 2)));
				dropcolor[i].setFillColor(sf::Color::Transparent); // invisible by default
			}
			dropcolor[0].setSize(sf::Vector2f(size->x * 0.8472f, size->y * 0.8181f)); // the first color does not cover the arrow part
			dropcolor[0].setOrigin(sf::Vector2f(float((size->x * 0.8472f) / 2 + (size->x * 0.9652f - size->x * 0.8472f) / 2), float((size->y * 0.8181f) / 2)));

			sprite->setOrigin(sf::Vector2f(float(size->x / 2), float(size->y / 2)));
			sprite->setOutlineColor(sf::Color::Yellow);

			selectedsprite->setOrigin(sf::Vector2f(float(size->x / 2), float(size->y / 2)));
			selectedsprite->setOutlineColor(sf::Color::Yellow);
			selectedsprite->setOutlineThickness(-2);
		}
		Dropdown(const unsigned short &elementnr, const std::string &text) : Dropdown(elementnr)
		{
			setMaintext(text);
		}
		Dropdown(const unsigned short &elementnr, const sf::Vector2f &size) : Dropdown(elementnr)
		{
			*this->size = size;

			sprite->setSize(size);
			sprite->setOrigin(sf::Vector2f(float(size.x / 2), float(size.y / 2)));
			sprite->setOutlineColor(sf::Color::Yellow);

			selectedsprite->setSize(size);
			selectedsprite->setOrigin(sf::Vector2f(float(size.x / 2), float(size.y / 2)));
			selectedsprite->setOutlineColor(sf::Color::Yellow);
			selectedsprite->setOutlineThickness(-2);

			for (unsigned short i = 0; i < elementnr; i++)
			{
				dropcolor[i].setSize(sf::Vector2f(size.x * 0.9652f, size.y * 0.8181f)); // a bit smaller than the whole dropdown
				dropcolor[i].setOrigin(sf::Vector2f(float((size.x * 0.9652f) / 2), float((size.y * 0.8181f) / 2)));
				dropcolor[i].setFillColor(sf::Color::Transparent);
			}
			dropcolor[0].setSize(sf::Vector2f(size.x * 0.8472f, size.y * 0.8181f)); // the first color does not cover the arrow part
			dropcolor[0].setOrigin(sf::Vector2f(float((size.x * 0.8472f) / 2), float((size.y * 0.8181f) / 2)));
		}
		~Dropdown()
		{
			delete size;
			delete sprite;
			delete selectedsprite;
			delete isPressed;
			delete isSelected;
			delete isDroppeddown;
			delete[] isActive;
			delete isInactive;
			delete elementnr;
			delete[] elementselected;
			delete maintext;
			delete[] droptext;
			delete[] dropcolor;
		}
		void setSelected(const sf::Vector2f & mouse);
		void handleInput(const sf::Event &event, sf::Sound & pressbutton);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		//setters
		void setTexture(const sf::Texture & texture, const sf::Font & font);
		void setPosition(const sf::Vector2f &position);
		void setSelectColor(const sf::Color &color);
		void setElementnr(const unsigned short &elementnr);
		void setScale(const sf::Vector2f &scale);
		void setMaintext(const std::string & text);
		void setDroptext(const unsigned short &i, const std::string & text);
		void setDroptextColor(const unsigned short &i, const sf::Color &color);
		void setDropColor(const unsigned short &i, const sf::Color &color);
		void setActive(const unsigned short &i, const bool & active);
		void setInactive(const bool & inactive);

		//getter
		bool getInactive() const { return *isInactive; }
		bool getActive(const unsigned short &i) const { return isActive[i]; }
		bool getDroppeddown() const { return *isDroppeddown; }
		std::string getDroptext(const unsigned short &i) const { return droptext[i].getString(); }
		sf::Color getDropColor(const unsigned short &i) const { return dropcolor[i].getFillColor(); }
		unsigned short getElementnr() const { return *elementnr; }
		sf::Vector2f getSize() const { return *size; }
	};
}