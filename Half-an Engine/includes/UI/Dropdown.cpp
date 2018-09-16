#include "Dropdown.h"

namespace UI
{
	void Dropdown::setSelected(const sf::Vector2f & mouse)
	{
		if (!isInactive)
		{
			isSelected = (sprite.getPosition().x - size.x / 2 * sprite.getScale().x <= mouse.x &&
				sprite.getPosition().x + size.x / 2 * sprite.getScale().x >= mouse.x &&
				sprite.getPosition().y - size.y / 2 * sprite.getScale().y <= mouse.y &&
				sprite.getPosition().y + size.y / 2 * sprite.getScale().y >= mouse.y);

			if (isDroppeddown)
			{
				for (unsigned int i = 1; i < elementnr; i++)
				{
					elementselected[i] = (sprite.getPosition().x - size.x / 2 * sprite.getScale().x <= mouse.x &&
						sprite.getPosition().x + size.x / 2 * sprite.getScale().x >= mouse.x &&
						sprite.getPosition().y - size.y / 2 * sprite.getScale().y + (size.y * i * sprite.getScale().y) <= mouse.y &&
						sprite.getPosition().y + size.y / 2 * sprite.getScale().y + (size.y * i * sprite.getScale().y) >= mouse.y);
				}
			}
		}
	}
	void Dropdown::handleInput(const sf::Event & event, sf::Sound & pressbutton)
	{
		if (event.mouseButton.button == sf::Mouse::Left && !isInactive)
		{
			if (event.type == sf::Event::MouseButtonPressed && isSelected)
			{
				if (pressbutton.getStatus() != sf::Music::Status::Playing && isPressed == false)
				{
					pressbutton.play();
				}

				isDroppeddown = true;
				isPressed = true;

				sprite.setTextureRect(sf::IntRect((int)size.x, 0, (int)size.x, int(size.y * elementnr)));
				sprite.setSize(sf::Vector2f(size.x, size.y * elementnr));
			}
			else if (event.type == sf::Event::MouseButtonReleased && isDroppeddown && !isSelected) //if dropped down & left mouse button pressed & mouse no more in the main position
			{
				for (unsigned int i = 1; i < elementnr; i++)
				{
					if (elementselected[i])
					{
						if (pressbutton.getStatus() != sf::Music::Status::Playing)
							pressbutton.play();

						isActive[i] = true;

						if (!isStatic)
						{
							setDroptext(0, droptext[i].getString());

							if (dropcolor[i].getFillColor() != sf::Color::Transparent) // if color is used
								setDropColor(0, dropcolor[i].getFillColor());
						}

						break;
					}
					else
						isActive[i] = false;
				}

				isDroppeddown = false;
				isSelected = false;
				isPressed = false;

				sprite.setTextureRect(sf::IntRect(0, 0, int(size.x), int(size.y)));
				sprite.setSize(size);
			}
		}

		if (isDroppeddown || isSelected)
			sprite.setOutlineThickness(-2);
		else
			sprite.setOutlineThickness(0);

		if (isDroppeddown) // if dropped down
		{
			for (unsigned int i = 1; i < elementnr; i++) // for every element
			{
				if (elementselected[i])
				{
					selectedsprite.setPosition(sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y + size.y*i *  sprite.getScale().y));
				}
			}
		}

	}
	void Dropdown::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if (isInactive)
			target.draw(inactivesprite, states);
		else
			target.draw(sprite, states);

		target.draw(maintext, states);
		target.draw(dropcolor[0], states);
		target.draw(droptext[0], states);

		if (isDroppeddown) // if dropped down
		{
			for (unsigned int i = 1; i < elementnr; i++) // for every element
			{
				target.draw(dropcolor[i], states); // draw corresponding color (if there is one)

				if (elementselected[i]) // if an element is selected draw selection on it
				{
					target.draw(selectedsprite, states);
				}
				target.draw(droptext[i], states); //draw corresponding text
			}
		}
	}
	void Dropdown::setTexture(const sf::Texture & texture, const sf::Font & font)
	{
		sprite.setTexture(&texture);
		sprite.setTextureRect(sf::IntRect(0, 0, int(size.x), int(size.y)));

		selectedsprite.setTexture(&texture);
		selectedsprite.setTextureRect(sf::IntRect(int(2 * size.x), 0, (int)size.x, (int)size.y));

		inactivesprite.setTexture(&texture);
		inactivesprite.setTextureRect(sf::IntRect(int(3 * size.x), 0, int(size.x), int(size.y)));

		maintext.setFont(font);

		this->maintext.setOrigin(this->maintext.getLocalBounds().left + this->maintext.getLocalBounds().width / 2.0f,
			this->maintext.getLocalBounds().top + this->maintext.getLocalBounds().height / 2.0f);

		for (unsigned int i = 0; i < elementnr; i++)
		{
			droptext[i].setFont(font);

			this->droptext[i].setOrigin(this->droptext[i].getLocalBounds().left + this->droptext[i].getLocalBounds().width / 2.0f,
				this->droptext[i].getLocalBounds().top + this->droptext[i].getLocalBounds().height / 2.0f);
		}
	}
	void Dropdown::setPosition(const sf::Vector2f & position)
	{
		sprite.setPosition(position);
		inactivesprite.setPosition(position);
		maintext.setPosition(sf::Vector2f(position.x, position.y - size.y * sprite.getScale().y));

		for (unsigned int i = 0; i < elementnr; i++)
		{
			droptext[i].setPosition(sf::Vector2f(position.x, position.y + size.y * i * sprite.getScale().y));
			dropcolor[i].setPosition(sf::Vector2f(position.x, position.y + size.y * i * sprite.getScale().y));
		}
	}
	void Dropdown::setSelectColor(const sf::Color & color)
	{
		sprite.setOutlineColor(color);
	}
	void Dropdown::setScale(const sf::Vector2f & scale)
	{
		sprite.setScale(scale);
		inactivesprite.setScale(scale);
		selectedsprite.setScale(scale);
		maintext.setCharacterSize(int(38 * scale.y));

		this->maintext.setOrigin(this->maintext.getLocalBounds().left + this->maintext.getLocalBounds().width / 2.0f,
			this->maintext.getLocalBounds().top + this->maintext.getLocalBounds().height / 2.0f);

		for (unsigned int i = 0; i < elementnr; i++)
		{
			droptext[i].setCharacterSize(int(38 * scale.y));

			this->droptext[i].setOrigin(this->droptext[i].getLocalBounds().left + this->droptext[i].getLocalBounds().width / 2.0f,
				this->droptext[i].getLocalBounds().top + this->droptext[i].getLocalBounds().height / 2.0f);

			dropcolor[i].setScale(scale);
		}
	}
	void Dropdown::setMaintext(const std::string & text)
	{
		maintext.setString(text);

		/*makes sure the text is in the right position*/
		this->maintext.setOrigin(this->maintext.getLocalBounds().left + this->maintext.getLocalBounds().width / 2.0f,
			this->maintext.getLocalBounds().top + this->maintext.getLocalBounds().height / 2.0f);
		
		maintext.setPosition(sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y - size.y * sprite.getScale().y));
		/*********************************************/
	}
	void Dropdown::setDroptext(const unsigned short & i, const std::string & text)
	{
		droptext[i].setString(text);

		/*makes sure the text is in the right position*/
		this->droptext[i].setOrigin(this->droptext[i].getLocalBounds().left + this->droptext[i].getLocalBounds().width / 2.0f,
			this->droptext[i].getLocalBounds().top + this->droptext[i].getLocalBounds().height / 2.0f);

		for (unsigned int i = 0; i < elementnr; i++)
			droptext[i].setPosition(sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y + size.y * i * sprite.getScale().y));
		/*********************************************/
	}
	void Dropdown::setDroptextColor(const unsigned short & i, const sf::Color & color)
	{
		droptext[i].setFillColor(color);
	}
	void Dropdown::setDropColor(const unsigned short & i, const sf::Color & color)
	{
		dropcolor[i].setFillColor(color);
		selectedsprite.setFillColor(sf::Color::Transparent);
	}
	void Dropdown::setElementnr(const unsigned short & elementnr)
	{
		this->elementnr = elementnr;
	}
	void Dropdown::setActive(const unsigned short & i, const bool & active)
	{
		isActive[i] = active;
	}
	void Dropdown::setInactive(const bool & inactive)
	{
		this->isInactive = inactive;
	}
}