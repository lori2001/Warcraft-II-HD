#pragma once
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"
#include <vector>
#include <iostream>

namespace UI
{
	class Dropdown : public sf::Drawable
	{
	private:
		sf::Vector2f size; // the size of a closed dropdown

		sf::RectangleShape sprite; // holds the main sprite
		sf::RectangleShape selectedsprite; //holds the outline for selected dropdown parts

		sf::Text abovetext; // text above dropdown

		bool isInactive = false; // if true make it grey and set it to unselectable
		bool isStatic = false; // if true droptext[0] and/or dropcolor[0] does not change

		int elementnr; // holds the number of elements in the dropdown
		std::vector<bool> isActive; //(vector) if true react(ex. change 800x600 resolution to 1000x600) - this is done in Menu.cpp
		std::vector<bool> elementSelected; // array of size elementnr | if a member is true it is selected | else not
		std::vector<sf::Text> droptext; // (array) text in dropdown
		std::vector<sf::RectangleShape> dropcolor; // (array) used only if you want colors instead of texts

	public:
		Dropdown(const int &elementnr, const sf::Vector2f &size)
		{
			this->size = size;
			this->elementnr = elementnr;

			abovetext.setFillColor(sf::Color::Yellow);

			sprite.setSize(size);
			sprite.setOrigin(sf::Vector2f(float(size.x / 2), float(size.y / 2)));
			sprite.setOutlineColor(sf::Color::Yellow);

			selectedsprite.setSize(size);
			selectedsprite.setOrigin(sf::Vector2f(float(size.x / 2), float(size.y / 2)));
			selectedsprite.setOutlineColor(sf::Color::Yellow);
			selectedsprite.setOutlineThickness(-2);

			// First element has to always be set up
			droptext.push_back(sf::Text());
			dropcolor.push_back(sf::RectangleShape());
			elementSelected.push_back(false);
			isActive.push_back(false);

			dropcolor[0].setSize(sf::Vector2f(size.x * 0.8472f, size.y * 0.8181f)); // the first color does not cover the arrow part
			dropcolor[0].setOrigin(sf::Vector2f(float((size.x * 0.8472f) / 2 + (size.x * 0.118) / 2), float((size.y * 0.8181f) / 2)));
			dropcolor[0].setFillColor(sf::Color::Transparent); // invisible by default
			droptext[0].setFillColor(sf::Color::Yellow); // set text color

			//sets up vectors for each element
			for (int i = 1; i < elementnr; i++) {

				/*  Set-ups  */
				droptext.push_back(sf::Text());
				dropcolor.push_back(sf::RectangleShape());
				elementSelected.push_back(false);
				isActive.push_back(false);
				/******************/

				droptext[i].setFillColor(sf::Color::Yellow); // set text color

				dropcolor[i].setSize(sf::Vector2f(size.x * 0.9652f, size.y * 0.8181f)); // a bit smaller than the whole dropdown
				dropcolor[i].setOrigin(sf::Vector2f(float((size.x * 0.9652f) / 2), float((size.y * 0.8181f) / 2)));
				dropcolor[i].setFillColor(sf::Color::Transparent); // invisible by default
			}
		}
		Dropdown(const int &elementnr) : Dropdown(elementnr, sf::Vector2f( 277,40 ))
		{
			//default consturctor inherits from constructor with parameter size but uses default values
		}
		Dropdown(const int &elementnr, const bool isStatic) : Dropdown(elementnr)
		{
			this->isStatic = isStatic;
		}
		Dropdown(const int &elementnr, const std::string &text) : Dropdown(elementnr)
		{
			setAbovetext(text);
		}

		void checkSelected(const sf::Vector2f & mouse);
		void handleInput(const sf::Event &event, sf::Sound & pressbutton);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		//setters
		void setTexture(const sf::Texture & texture, const sf::Font & font);
		void setPosition(const sf::Vector2f &position);
		void setSelectColor(const sf::Color &color);
		//void setElementnr(const unsigned int &elementnr);
		void setScale(const sf::Vector2f &scale);
		void setAbovetext(const std::string & text);
		void setDroptext(const unsigned int &i, const std::string & text);
		void setDroptextColor(const unsigned int &i, const sf::Color &color);
		void setDropColor(const unsigned int &i, const sf::Color &color);
		void setActive(const unsigned int &i, const bool & active);
		void setInactive(const bool & inactive);

		//getters
		sf::Vector2f getPosition() const { return sprite.getPosition(); }
		bool getInactive() const { return isInactive; }
		bool getActive(const unsigned int &i) const { return isActive[i]; }
		bool getDroppeddown() const { return isActive[0]; }
		std::string getDroptext(const unsigned int &i) const { return droptext[i].getString(); }
		sf::Color getDropColor(const unsigned int &i) const { return dropcolor[i].getFillColor(); }
		int getElementnr() const { return elementnr; }
		sf::Vector2f getSize() const { return size; }
	};
}