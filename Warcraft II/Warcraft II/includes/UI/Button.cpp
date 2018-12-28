#include "Button.h"

namespace UI
{
	void Button::checkSelected(const sf::Vector2f & mouse)
	{
		//checks if the mouse and the button intersect
		isSelected = sprite.getGlobalBounds().intersects(sf::FloatRect(mouse, { 1,1 })); //mouse has the size of 1,1

		//if they do, the outline appears
		if (isSelected)
			sprite.setOutlineThickness(-2);
		else //else, the outline disappears
			sprite.setOutlineThickness(0);
	}
	void Button::handleInput(const sf::Event & event, sf::Sound & pressbutton)
	{
		// if the mouse intersects with the button and leftmousebutton is enabled
		if (event.mouseButton.button == sf::Mouse::Left && isSelected)
		{
			if (event.type == sf::Event::MouseButtonPressed)
			{
				// play button sound
				if (pressbutton.getStatus() != sf::Music::Status::Playing)
					pressbutton.play();

				//create the "pressed in" visual effect
				sprite.setTextureRect(sf::IntRect((int)size.x, 0, (int)size.x, (int)size.y));
				text.setPosition(sf::Vector2f(sprite.getPosition().x + (3 * sprite.getScale().x), sprite.getPosition().y + (3 * sprite.getScale().y)));

				//the button has been pressed / take action when released
				isPressed = true;
			}
			else if (event.type == sf::Event::MouseButtonReleased && isPressed)
			{
				//take action
				isActive = true;
			}
		}

		// if the mouse looses touch with the button
		if (!isSelected)
		{
			//reset visual effects
			sprite.setTextureRect(sf::IntRect(0, 0, (int)size.x, (int)size.y));
			text.setPosition(sprite.getPosition());

			//make inactive
			isPressed = false;
		}
	}
	void Button::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		target.draw(sprite, states);
		target.draw(text, states);
	}
	bool Button::hasBeenActivated()
	{
		bool ret = isActive;
		isActive = false;
		return ret;
	}
	void Button::setTexture(const sf::Texture & texture)
	{
		//sets sprite texture
		sprite.setTexture(&texture);

		//defaults to the first part of the buttontexture
		sprite.setTextureRect(sf::IntRect(0, 0, int(size.x), int(size.y)));
	}
	void Button::setTexture(const sf::Texture & texture, const sf::Font &font)
	{
		//sets sprite texture
		this->setTexture(texture);

		//sets font
		text.setFont(font);

		//centers text with the new font in mind
		this->text.setOrigin(this->text.getLocalBounds().left + this->text.getLocalBounds().width / 2.0f,
			this->text.getLocalBounds().top + this->text.getLocalBounds().height / 2.0f);
	}
	void Button::setPosition(const sf::Vector2f & position)
	{
		//sets position of the sprite
		sprite.setPosition(position);

		//the text gets the position the sprite does
		text.setPosition(position);
	}
	void Button::setSelectColor(const sf::Color & color)
	{
		//if selected this will be the outline color
		sprite.setOutlineColor(color);
	}
	void Button::setScale(const sf::Vector2f & scale)
	{
		//changes sprite scale
		sprite.setScale(scale);

		//changes text size
		text.setCharacterSize(int(38 * scale.y));

		//centers the newly sized text
		this->text.setOrigin(this->text.getLocalBounds().left + this->text.getLocalBounds().width / 2.0f,
			this->text.getLocalBounds().top + this->text.getLocalBounds().height / 2.0f);
	}
	void Button::setString(const std::string & text)
	{
		//sets the new string to the text
		this->text.setString(text);

		//centers the new string of text
		this->text.setOrigin(this->text.getLocalBounds().left + this->text.getLocalBounds().width / 2.0f,
			this->text.getLocalBounds().top + this->text.getLocalBounds().height / 2.0f);
	}
}