#include "TextHolder.h"

namespace UI
{
	void TextHolder::setSelected(const sf::Vector2f & mouse)
	{
		*isSelected = (sprite->getPosition().x - size->x / 2 * sprite->getScale().x <= mouse.x &&
			sprite->getPosition().x + size->x / 2 * sprite->getScale().x >= mouse.x &&
			sprite->getPosition().y - size->y / 2 * sprite->getScale().y <= mouse.y &&
			sprite->getPosition().y + size->y / 2 * sprite->getScale().y >= mouse.y);

		if (*isSelected)
			sprite->setOutlineThickness(-2);
		else
			sprite->setOutlineThickness(0);
	}
	void TextHolder::handleInput(const sf::Event & event, sf::Sound & pressbutton)
	{//TODO: if resolution changes text goes out of bound
		if (*isSelected && event.mouseButton.button == sf::Mouse::Left && event.type == sf::Event::MouseButtonPressed)
		{ // if pressed and selected
			if (pressbutton.getStatus() != sf::Music::Status::Playing && !*isActive) // play sound
				pressbutton.play();

			text->setString(""); //resets text

			//sets to center after wiping text
			cursor->setPosition(sf::Vector2f(text->getPosition().x + text->getLocalBounds().width / 2 + 2 * sprite->getScale().x, text->getPosition().y));

			*isActive = true; //makes active so writing may occur
		}
		else if (*isActive == true && event.mouseButton.button == sf::Mouse::Left && event.type == sf::Event::MouseButtonPressed)
		{ // if mouse button pressed anywhere else
			*isActive = false; //make inactive
			*hasChanged = true; //signal that string has changed
		}

		if (*isActive)
		{
			std::string temp = text->getString(); // holds the text before editing
			std::string txt = (sf::String(event.text.unicode)); //gets the text entered

			if (event.type == sf::Event::TextEntered && (temp.size() < 30 || txt == "\b"))
			{// if text entered and we have either less caracters than 30 or get a /b caracter

				if (txt == "\b" && temp.size() > 0) //if backslash pressed
				{
					temp.erase(temp.size() - 1); // erase the last character
				}
				else if (text->getLocalBounds().width < (size->x - 20) * sprite->getScale().x)
				{ //checks the current size of the text, to not exceed corners

					if (temp == "" || (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)))
					{ //if this is the first character or shift is pressed make the entered text big
						txt[0] = toupper(txt[0]);
					}

					temp += txt;
					//add new character to the temp string
				}

				text->setString(temp); //set new text on screen

				//center it
				this->text->setOrigin(this->text->getLocalBounds().left + this->text->getLocalBounds().width / 2.0f,
					this->text->getLocalBounds().top + this->text->getLocalBounds().height / 2.0f);

				//sets cursor after new bounds
				cursor->setPosition(sf::Vector2f(text->getPosition().x + text->getLocalBounds().width / 2 + 2 * sprite->getScale().x, text->getPosition().y));
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			{ //if enter pressed make inactive
				*isActive = false;
				*hasChanged = true; //signal that string has changed
			}
		}
	}
	void TextHolder::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		target.draw(*sprite, states);
		target.draw(*text, states);
		target.draw(*maintext, states);

		if (*isActive)
			target.draw(*cursor, states);
	}
	void TextHolder::setTexture(const sf::Texture & texture, const sf::Font & font)
	{
		sprite->setTexture(&texture);
		text->setFont(font);
		maintext->setFont(font);
		cursor->setFont(font);

		cursor->setString("|");

		this->text->setOrigin(this->text->getLocalBounds().left + this->text->getLocalBounds().width / 2.0f,
			this->text->getLocalBounds().top + this->text->getLocalBounds().height / 2.0f);

		this->maintext->setOrigin(this->maintext->getLocalBounds().left + this->maintext->getLocalBounds().width / 2.0f,
			this->maintext->getLocalBounds().top + this->maintext->getLocalBounds().height / 2.0f);

		this->cursor->setOrigin(this->cursor->getLocalBounds().left + this->cursor->getLocalBounds().width / 2.0f,
			this->cursor->getLocalBounds().top + this->cursor->getLocalBounds().height / 2.0f);
	}
	void TextHolder::setPosition(const sf::Vector2f & position)
	{
		sprite->setPosition(position);
		text->setPosition(position);
		maintext->setPosition(sf::Vector2f(position.x, position.y - size->y * sprite->getScale().y));
		cursor->setPosition(sf::Vector2f(position.x + text->getLocalBounds().width / 2 + 2 * sprite->getScale().x, position.y));
	}
	void TextHolder::setScale(const sf::Vector2f & scale)
	{
		sprite->setScale(scale);

		std::string temp = text->getString();

		if (text->getLocalBounds().width >= (size->x - 20) * sprite->getScale().x)
			(*textsize)--;
		else if (text->getLocalBounds().width < (size->x - 20) * sprite->getScale().x && *lastscale != scale)
			*textsize = 18;

		text->setCharacterSize(int(*textsize * scale.y));

		maintext->setCharacterSize(int(38 * scale.y));
		cursor->setCharacterSize(int(38 * scale.y));

		*lastscale = scale;

		this->text->setOrigin(this->text->getLocalBounds().left + this->text->getLocalBounds().width / 2.0f,
			this->text->getLocalBounds().top + this->text->getLocalBounds().height / 2.0f);

		this->maintext->setOrigin(this->maintext->getLocalBounds().left + this->maintext->getLocalBounds().width / 2.0f,
			this->maintext->getLocalBounds().top + this->maintext->getLocalBounds().height / 2.0f);

		this->cursor->setOrigin(this->cursor->getLocalBounds().left + this->cursor->getLocalBounds().width / 2.0f,
			this->cursor->getLocalBounds().top + this->cursor->getLocalBounds().height / 2.0f);
	}
	void TextHolder::setString(const std::string & text)
	{
		this->text->setString(text);

		this->text->setOrigin(this->text->getLocalBounds().left + this->text->getLocalBounds().width / 2.0f,
			this->text->getLocalBounds().top + this->text->getLocalBounds().height / 2.0f);
	}
	void TextHolder::setMaintext(const std::string & text)
	{
		maintext->setString(text);

		this->maintext->setOrigin(this->maintext->getLocalBounds().left + this->maintext->getLocalBounds().width / 2.0f,
			this->maintext->getLocalBounds().top + this->maintext->getLocalBounds().height / 2.0f);
	}
}