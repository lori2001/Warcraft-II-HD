#pragma once
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"

namespace UI
{
	//TODO: Button auto inactive
	class Button : public sf::Drawable
	{
	private:
		sf::Vector2f size; //sprite size

		sf::RectangleShape sprite;// holds main sprite
		sf::Text text; // a text to be on the button

		bool isPressed = false;
		bool isSelected = false; //if mouse is hovered over the button this is true
		bool isActive = false; //this is true when the button is pressed upon
	public:
		Button(const sf::Vector2f &size)
		{
			this->size = size;
			sprite.setSize(size);

			// copy-pasted from Button() in order to set the origin correctly
			text.setCharacterSize(38);
			text.setFillColor(sf::Color::Yellow);

			sprite.setOrigin(sf::Vector2f(this->size.x / 2, this->size.y / 2));
			sprite.setOutlineColor(sf::Color::Yellow);
		}
		Button() : Button(sf::Vector2f(430, 50)) 
		{
			//default consturctor inherits from constructor with parameter size but uses default values
		}
		Button(const std::string &text) : Button()
		{
			this->text.setString(text);
		}
		Button(const std::string &text, const sf::Vector2f &position) : Button(text)
		{
			sprite.setPosition(position);
			this->text.setPosition(position);
		}
		//class-specific functions
		void checkSelected(const sf::Vector2f & mouse);
		void handleInput(const sf::Event &event, sf::Sound & pressbutton);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		//returns isActive and sets it to false
		bool hasBeenActivated();
		
		//setters
		void setTexture(const sf::Texture & texture);
		void setTexture(const sf::Texture & texture, const sf::Font &font);
		void setPosition(const sf::Vector2f &position);
		void setSelectColor(const sf::Color &color);
		void setScale(const sf::Vector2f &scale);
		void setString(const std::string & text);

		//getters
		bool getSelected() const { return isSelected; }
		sf::Vector2f getScale() const { return  sprite.getScale(); }
		sf::Vector2f getPosition() const { return sprite.getPosition(); }
		sf::Vector2f getSize() const { return size; }
	};
}