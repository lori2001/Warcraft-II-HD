#include "Button.h"

namespace UI
{
	void Button::setSelected(const sf::Vector2f & mouse)
	{
		//checks if the mouse and the button intersect
		isSelected = (sprite.getPosition().x - this->size.x / 2 * sprite.getScale().x <= mouse.x &&
			sprite.getPosition().x + this->size.x / 2 * sprite.getScale().x >= mouse.x &&
			sprite.getPosition().y - this->size.y / 2 * sprite.getScale().y <= mouse.y &&
			sprite.getPosition().y + this->size.y / 2 * sprite.getScale().y >= mouse.y);

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
				if (pressbutton.getStatus() != sf::Music::Status::Playing) // play button sound
					pressbutton.play();

				//create the "pressed in" visual effect
				sprite.setTextureRect(sf::IntRect((int)size.x, 0, (int)size.x, (int)size.y));

				//the button has been pressed / take action when released
				isPressed = true;
			}
			else if (event.type == sf::Event::MouseButtonReleased && isPressed)
			{
				//take action
				isActive = true;
			}
		}

		// if the mouse looses touch with the button while pressed, make the button inactive
		if (event.mouseButton.button == sf::Mouse::Left && event.type == sf::Event::MouseButtonReleased || !isSelected)
		{
			sprite.setTextureRect(sf::IntRect(0, 0, (int)size.x, (int)size.y));
			isPressed = false;
		}

		//if the button is pressed the text moves down and right a bit
		if (isPressed && isSelected)
			text.setPosition(sf::Vector2f(sprite.getPosition().x + (3 * sprite.getScale().x), sprite.getPosition().y + (3 * sprite.getScale().y)));
		else //else the text gets the position the sprite does
			text.setPosition(sprite.getPosition());
	}
	void Button::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		target.draw(sprite, states);
		target.draw(text, states);
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
	void Button::setTexture(const sf::Texture & texture)
	{
		//sets sprite texture
		sprite.setTexture(&texture);

		//uses the first part of the buttontexture
		sprite.setTextureRect(sf::IntRect(0, 0, int(size.x), int(size.y)));
	}
	void Button::setPosition(const sf::Vector2f & position)
	{
		//sets position of the sprite
		sprite.setPosition(position);

		// the text gets the position the sprite does
		text.setPosition(position);
	}
	void Button::setSelectColor(const sf::Color & color)
	{
		//in case selected this color will be the outline
		sprite.setOutlineColor(color);
	}
	//void Button::setSize(const sf::Vector2f & size)
	//{
	//	sprite.setSize(size);
	//}
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
	void Button::setActive(const bool & active)
	{
		//mostly gets parameter "false"
		//it enables/disables the action the button was doing ex.going into options
		this->isActive = active;
	}
}