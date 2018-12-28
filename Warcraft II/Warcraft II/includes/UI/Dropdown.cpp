#include "Dropdown.h"

namespace UI
{
	void Dropdown::checkSelected(const sf::Vector2f & mouse)
	{
		if (!isInactive)
		{
			//first element is the same as the closed-up sprite
			sf::FloatRect mainrect(sprite.getGlobalBounds().left, sprite.getGlobalBounds().top, size.x * sprite.getScale().x, size.y * sprite.getScale().y);

			//check if it collides with mouse
			elementSelected[0] = mainrect.intersects(sf::FloatRect(mouse, { 1,1 }));

			//if the main element has been pressed
			if (isActive[0])
			{
				//iterate through each element of the dropdown
				for (int i = 1; i < elementnr; i++)
				{
					//creates a FloatRect class for the current elements position
					//keep in mind that sprite is in extended mode right now
					sf::FloatRect thisrect (
						sprite.getGlobalBounds().left,
						sprite.getGlobalBounds().top + (size.y * sprite.getScale().y * i), // moves down by the amount of i
						size.x * sprite.getScale().x,
						size.y * sprite.getScale().y
						);

					//checks intersection with mouse for each element
					elementSelected[i] = thisrect.intersects(sf::FloatRect(mouse ,{ 1,1 }));
				}
			}
		}
	}
	void Dropdown::handleInput(const sf::Event & event, sf::Sound & pressbutton)
	{
		//if the leftmousebutton is enabled and this dropdown is active
		if (event.mouseButton.button == sf::Mouse::Left && !isInactive)
		{
			//if mouse is pressed and the main element is selected
			if (event.type == sf::Event::MouseButtonPressed && elementSelected[0])
			{
				//play button sound
				if (pressbutton.getStatus() != sf::Music::Status::Playing && isActive[0] == false)
					pressbutton.play();

				//drop down
				sprite.setTextureRect(sf::IntRect((int)size.x, 0, (int)size.x, int(size.y * elementnr)));
				sprite.setSize(sf::Vector2f(size.x, size.y * elementnr));
			
				//set dropdown bool to true
				isActive[0] = true;
			}
			//if dropped down & left mouse button released & the mouse isn't on the main element
			else if (event.type == sf::Event::MouseButtonReleased && isActive[0] && !elementSelected[0])
			{
				//iterate through each element
				for (int i = 0; i < elementnr; i++)
				{
					if (elementSelected[i]) //check if selected
					{
						//play button sound
						if (pressbutton.getStatus() != sf::Music::Status::Playing)
							pressbutton.play();

						//make button active
						isActive[i] = true;

						//if the dropdown's displayed information should change
						if (!isStatic)
						{
							//change text
							setDroptext(0, droptext[i].getString());

							if (dropcolor[i].getFillColor() != sf::Color::Transparent) // if color is used
								setDropColor(0, dropcolor[i].getFillColor()); //change color
						}

						break;
					}
					else //if not selected make sure its inactive
						isActive[i] = false;
				}

				// minimalize the dropdown back 
				sprite.setTextureRect(sf::IntRect(0, 0, int(size.x), int(size.y)));
				sprite.setSize(size);
			}
		}

		//if dropped down or first element is selected
		if (isActive[0] || elementSelected[0])
			sprite.setOutlineThickness(-2);
		else
			sprite.setOutlineThickness(0);

		if (isActive[0]) // if dropped down
		{
			for (int i = 1; i < elementnr; i++) // for every element
			{
				if (elementSelected[i]) //if the element is selected
				{
					//set the position of the selection rectangle properly
					selectedsprite.setPosition(sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y + size.y * i *  sprite.getScale().y));

					//break because only one can be selected at once
					break;
				}
			}
		}
	}
	void Dropdown::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(sprite, states);
		target.draw(abovetext, states);
		target.draw(dropcolor[0], states);
		target.draw(droptext[0], states);

		if (isActive[0]) // if dropped down
		{
			for (int i = 1; i < elementnr; i++) // for each element
			{
				target.draw(dropcolor[i], states); // draw corresponding color (if there is one)

				if (elementSelected[i]) // if any of the elements is selected
					target.draw(selectedsprite, states); // draw selection

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

		abovetext.setFont(font);

		this->abovetext.setOrigin(this->abovetext.getLocalBounds().left + this->abovetext.getLocalBounds().width / 2.0f,
			this->abovetext.getLocalBounds().top + this->abovetext.getLocalBounds().height / 2.0f);

		for (int i = 0; i < elementnr; i++)
		{
			droptext[i].setFont(font);

			this->droptext[i].setOrigin(this->droptext[i].getLocalBounds().left + this->droptext[i].getLocalBounds().width / 2.0f,
				this->droptext[i].getLocalBounds().top + this->droptext[i].getLocalBounds().height / 2.0f);
		}
	}
	void Dropdown::setPosition(const sf::Vector2f & position)
	{
		sprite.setPosition(position);
		abovetext.setPosition(sf::Vector2f(position.x, position.y - size.y * sprite.getScale().y));

		for (int i = 0; i < elementnr; i++)
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
		selectedsprite.setScale(scale);
		abovetext.setCharacterSize(int(38 * scale.y));

		this->abovetext.setOrigin(this->abovetext.getLocalBounds().left + this->abovetext.getLocalBounds().width / 2.0f,
			this->abovetext.getLocalBounds().top + this->abovetext.getLocalBounds().height / 2.0f);

		for (int i = 0; i < elementnr; i++)
		{
			droptext[i].setCharacterSize(int(38 * scale.y));

			this->droptext[i].setOrigin(this->droptext[i].getLocalBounds().left + this->droptext[i].getLocalBounds().width / 2.0f,
				this->droptext[i].getLocalBounds().top + this->droptext[i].getLocalBounds().height / 2.0f);

			dropcolor[i].setScale(scale);
		}
	}
	void Dropdown::setAbovetext(const std::string & text)
	{
		abovetext.setString(text);

		/*makes sure the text is in the right position*/
		this->abovetext.setOrigin(this->abovetext.getLocalBounds().left + this->abovetext.getLocalBounds().width / 2.0f,
			this->abovetext.getLocalBounds().top + this->abovetext.getLocalBounds().height / 2.0f);
		
		abovetext.setPosition(sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y - size.y * sprite.getScale().y));
		/*********************************************/
	}
	void Dropdown::setDroptext(const unsigned int & i, const std::string & text)
	{
		droptext[i].setString(text);

		/*makes sure the text is in the right position*/
		this->droptext[i].setOrigin(this->droptext[i].getLocalBounds().left + this->droptext[i].getLocalBounds().width / 2.0f,
			this->droptext[i].getLocalBounds().top + this->droptext[i].getLocalBounds().height / 2.0f);

		for (int i = 0; i < elementnr; i++)
			droptext[i].setPosition(sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y + size.y * i * sprite.getScale().y));
		/*********************************************/
	}
	void Dropdown::setDroptextColor(const unsigned int & i, const sf::Color & color)
	{
		droptext[i].setFillColor(color);
	}
	void Dropdown::setDropColor(const unsigned int & i, const sf::Color & color)
	{
		dropcolor[i].setFillColor(color);
		selectedsprite.setFillColor(sf::Color::Transparent);
	}
	//void Dropdown::setElementnr(const unsigned int & elementnr)
	//{
	//	this->elementnr = elementnr;
	//}
	void Dropdown::setActive(const unsigned int & i, const bool & active)
	{
		isActive[i] = active;
	}
	void Dropdown::setInactive(const bool & inactive)
	{
		this->isInactive = inactive;

		if(isInactive)
			sprite.setTextureRect(sf::IntRect(int(3 * size.x), 0, int(size.x), int(size.y)));
		else
			selectedsprite.setTextureRect(sf::IntRect(int(2 * size.x), 0, (int)size.x, (int)size.y));
	}
}