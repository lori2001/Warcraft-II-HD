#pragma once
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"

namespace UI
{
	//TODO: Button auto inactive
	class Button : public sf::Drawable
	{
	private:
		sf::Vector2f size{ 430, 50 }; //this is the sprite's size

		sf::RectangleShape sprite{ size }; //creates a rect with that size
		sf::Text text; // a text to be on the button

		bool isPressed = false;
		bool isSelected = false; //if mouse is hovered over the button this is true
		bool isActive = false; //this is true when the button is pressed upon
	public:
		Button()
		{
			text.setFillColor(sf::Color::Yellow);

			sprite.setOrigin(sf::Vector2f(this->size.x / 2, this->size.y / 2));
			sprite.setOutlineColor(sf::Color::Yellow);
		}
		Button(const sf::Vector2f &size)
		{
			this->size = size;
			sprite.setSize(size);

			text.setFillColor(sf::Color::Yellow);

			sprite.setOrigin(sf::Vector2f(this->size.x / 2, this->size.y / 2));
			sprite.setOutlineColor(sf::Color::Yellow);
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
		void setSelected(const sf::Vector2f & mouse);
		void handleInput(const sf::Event &event, sf::Sound & pressbutton);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		
		//setters
		void setTexture(const sf::Texture & texture, const sf::Font &font);
		void setTexture(const sf::Texture & texture);
		void setPosition(const sf::Vector2f &position);
		void setSelectColor(const sf::Color &color);
		//this function has been DISABLED due to being unused and buggy
		//void setSize(const sf::Vector2f &size);
		void setScale(const sf::Vector2f &scale);
		void setString(const std::string & text);
		void setActive(const bool & active);

		//getters
		bool getActive() const { return isActive; }
		bool getSelected() const { return isSelected; }
		sf::Vector2f getScale() const { return  sprite.getScale(); }
		sf::Vector2f getPosition() const { return sprite.getPosition(); }
		sf::Vector2f getSize() const { return size; }
	};
}