#include "Switch.h"

namespace UI
{
	void Switch::setSelected(const sf::Vector2f & mouse)
	{
		if (isCircle)
		{
			isSelected = (circle.getPosition().x - this->csize / 2 * circle.getScale().x <= mouse.x &&
				circle.getPosition().x + this->csize / 2 * circle.getScale().x >= mouse.x &&
				circle.getPosition().y - this->csize / 2 * circle.getScale().y <= mouse.y &&
				circle.getPosition().y + this->csize / 2 * circle.getScale().y >= mouse.y);

			if (isSelected)
				circle.setOutlineThickness(-2);
			else
				circle.setOutlineThickness(0);
		}
		else
		{
			isSelected = (rect.getPosition().x - this->rsize.x / 2 * rect.getScale().x <= mouse.x &&
				rect.getPosition().x + this->rsize.x / 2 * rect.getScale().x >= mouse.x &&
				rect.getPosition().y - this->rsize.y / 2 * rect.getScale().y <= mouse.y &&
				rect.getPosition().y + this->rsize.y / 2 * rect.getScale().y >= mouse.y);
		}
	}
	void Switch::handleInput(const sf::Event & event, sf::Sound & pressbutton)
	{
		if (event.mouseButton.button == sf::Mouse::Left && isSelected)
		{
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (pressbutton.getStatus() != sf::Music::Status::Playing)// && isPressed == false)
				{
					pressbutton.play();
				}
				isPressed = true;
			}
			else if (event.type == sf::Event::MouseButtonReleased && isPressed)
			{
				if (!isActive)
					isActive = true;
				else
					isActive = false;
			}
		}

		if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left || !isSelected)
			isPressed = false;

		if (isCircle)
		{
			if (isPressed)
			{
				if (isActive)
					circle.setTextureRect(sf::IntRect(int(3 * csize), int(rsize.y), int(csize), int(csize)));
				else
					circle.setTextureRect(sf::IntRect(int(csize), int(rsize.y), int(csize), int(csize)));
			}
			else
			{
				if (isActive)
					circle.setTextureRect(sf::IntRect(int(2 * csize), int(rsize.y), int(csize), int(csize)));
				else
					circle.setTextureRect(sf::IntRect(0, int(rsize.y), int(csize), int(csize)));
			}
		}
		else
		{
			if (isPressed)
			{
				if (isActive)
					rect.setTextureRect(sf::IntRect(int(3 * rsize.x), 0, int(rsize.x), int(rsize.y)));
				else
					rect.setTextureRect(sf::IntRect(int(rsize.x), 0, int(rsize.x), int(rsize.y)));
			}
			else
			{
				if (isActive)
					rect.setTextureRect(sf::IntRect(int(2 * rsize.x), 0, int(rsize.x), int(rsize.y)));
				else
					rect.setTextureRect(sf::IntRect(0, 0, int(rsize.x), int(rsize.y)));
			}
		}
	}
	void Switch::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		if (isCircle)
		{
			target.draw(circle, states);
		}
		else
		{
			target.draw(rect, states);

			if (isSelected)
				target.draw(rectOutline, states);
		}

		target.draw(text, states);
	}
	void Switch::setTexture(const sf::Texture & texture, const sf::Font & font)
	{
		if (isCircle)
		{
			circle.setTexture(&texture);
			circle.setTextureRect(sf::IntRect(0, int(rsize.y), int(csize), int(csize)));
		}
		else
		{
			rect.setTexture(&texture);
			rect.setTextureRect(sf::IntRect(0, 0, int(rsize.x), int(rsize.y)));
		}

		text.setFont(font);

		this->text.setOrigin(this->text.getLocalBounds().left + this->text.getLocalBounds().width / 2.0f,
			this->text.getLocalBounds().top + this->text.getLocalBounds().height / 2.0f);
	}
	void Switch::setPosition(const sf::Vector2f & position)
	{
		if (isCircle)
		{
			circle.setPosition(position);
			text.setPosition(sf::Vector2f(position.x + circle.getRadius() + text.getLocalBounds().width / 2 + 5 * circle.getScale().x, position.y));
		}
		else
		{
			rect.setPosition(position);
			rectOutline.setPosition(position);
			text.setPosition(sf::Vector2f(position.x + (rect.getSize().x * rect.getScale().x) / 2 + text.getLocalBounds().width / 2, position.y - 4 * rect.getScale().y));
		}
	}
	void Switch::setScale(const sf::Vector2f & scale)
	{
		if (isCircle)
			circle.setScale(scale);
		else
		{
			rect.setScale(scale);
			rectOutline.setScale(scale);
		}

		text.setCharacterSize(int(32 * scale.y));

		this->text.setOrigin(this->text.getLocalBounds().left + this->text.getLocalBounds().width / 2.0f,
			this->text.getLocalBounds().top + this->text.getLocalBounds().height / 2.0f);
	}
	void Switch::setText(const std::string & text)
	{
		this->text.setString(text);
		
		this->text.setOrigin(this->text.getLocalBounds().left + this->text.getLocalBounds().width / 2.0f,
			this->text.getLocalBounds().top + this->text.getLocalBounds().height / 2.0f);
	}
}