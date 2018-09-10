#include "Slider.h"

namespace UI
{
	void Slider::setSelected(const sf::Vector2f & mouse)
	{
		iscSelected = (slider.getPosition().x - csize.x / 2 * slider.getScale().x <= mouse.x &&
			slider.getPosition().x + csize.x / 2 * slider.getScale().x >= mouse.x &&
			slider.getPosition().y - csize.y / 2 * slider.getScale().y <= mouse.y &&
			slider.getPosition().y + csize.y / 2 * slider.getScale().y >= mouse.y);

		isrSelected = (slider.getPosition().x + csize.x / 2 * slider.getScale().x <= mouse.x &&
			slider.getPosition().x + csize.x / 2 * slider.getScale().x + lrsize.x * slider.getScale().x + 1 * slider.getScale().x >= mouse.x &&
			slider.getPosition().y - lrsize.y / 2 * slider.getScale().y <= mouse.y &&
			slider.getPosition().y + lrsize.y / 2 * slider.getScale().y >= mouse.y);

		islSelected = (slider.getPosition().x - csize.x / 2 * slider.getScale().x - lrsize.x * slider.getScale().x - 1 * slider.getScale().x <= mouse.x &&
			slider.getPosition().x - csize.x / 2 * slider.getScale().x >= mouse.x &&
			slider.getPosition().y - lrsize.y / 2 * slider.getScale().y <= mouse.y &&
			slider.getPosition().y + lrsize.y / 2 * slider.getScale().y >= mouse.y);
	}
	void Slider::handleInput(const sf::Event & event, const sf::Vector2f & mouse, sf::Sound & pressbutton)
	{
		const unsigned short lastlevel = level;
		assert(0 <= level && level <= 10);

		if (event.mouseButton.button == sf::Mouse::Left && event.type == sf::Event::MouseButtonPressed) // if left button is pressed
		{
			if (pressbutton.getStatus() != sf::Music::Status::Playing && (islSelected || isrSelected || iscSelected))
				pressbutton.play();

			isPressed = true;

			if (isrSelected && level < 10)
			{
				(level)++;
			}
			else if (islSelected && level > 0)
			{
				(level)--;
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || event.mouseButton.button == sf::Mouse::Left) // if left button is held
		{
			if (iscSelected && isPressed)
			{
				const float unit = csize.x / 11 * slider.getScale().x;
				unsigned short measure = 0;
				for (float i = slider.getPosition().x - csize.x / 2 * slider.getScale().x + unit; measure <= 10; i += unit)
				{
					if (mouse.x > i - unit && mouse.x < i)
					{
						level = measure;
						break;
					}
					measure++;
				}
			}
		}

		if (!islSelected && !isrSelected && !iscSelected)
			isPressed = false;

		if (lastlevel != level)
		{
			//level changed, this changes the position of the button
			button.setPosition(sf::Vector2f(slider.getPosition().x - csize.x / 2 * slider.getScale().x + bsize.x / 2 * slider.getScale().x + (csize.x - bsize.x) * (level) / 10 * slider.getScale().x, slider.getPosition().y));
			//sets isActive to true thus taking action
			isActive = true;
		}
	}
	void Slider::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		target.draw(slider, states);

		if (iscSelected)
			target.draw(centerOutline, states);
		else if (isrSelected)
			target.draw(rightOutline, states);
		else if (islSelected)
			target.draw(leftOutline, states);

		target.draw(button, states);
		target.draw(text, states);
	}
	void Slider::setTexture(const sf::Texture & sliderT, const sf::Texture & buttonT, const sf::Font & font)
	{
		slider.setTexture(&sliderT);
		button.setTexture(&buttonT);
		text.setFont(font);
	}
	void Slider::setPosition(const sf::Vector2f & position)
	{
		slider.setPosition(position);
		button.setPosition(sf::Vector2f(position.x - csize.x / 2 * slider.getScale().x + bsize.x / 2 * slider.getScale().x + (csize.x - bsize.x) * level / 10 * slider.getScale().x, position.y));
		centerOutline.setPosition(position);
		leftOutline.setPosition(sf::Vector2f(position.x - csize.x / 2 * slider.getScale().x - lrsize.x / 2 * slider.getScale().x - 1 * slider.getScale().x, position.y));
		rightOutline.setPosition(sf::Vector2f(position.x + csize.x / 2 * slider.getScale().x + lrsize.x / 2 * slider.getScale().x + 1 * slider.getScale().x, position.y));
		text.setPosition(sf::Vector2f(position.x, position.y - (csize.y + 3) * slider.getScale().y));
	}
	void Slider::setSelectColor(const sf::Color & color)
	{
		centerOutline.setOutlineColor(color);
		leftOutline.setOutlineColor(color);
		rightOutline.setOutlineColor(color);
	}
	void Slider::setScale(const sf::Vector2f & scale)
	{
		slider.setScale(scale);
		button.setScale(scale);
		centerOutline.setScale(scale);
		leftOutline.setScale(scale);
		rightOutline.setScale(scale);
		text.setCharacterSize(int(38 * scale.y));

		this->text.setOrigin(this->text.getLocalBounds().left + this->text.getLocalBounds().width / 2.0f,
			this->text.getLocalBounds().top + this->text.getLocalBounds().height / 2.0f);
	}
	void Slider::setString(const std::string & text)
	{
		this->text.setString(text);

		this->text.setOrigin(this->text.getLocalBounds().left + this->text.getLocalBounds().width / 2.0f,
			this->text.getLocalBounds().top + this->text.getLocalBounds().height / 2.0f);
	}
	void Slider::setActive(const bool & active)
	{
		this->isActive = active;
	}
	void Slider::setLevel(const unsigned short & level)
	{
		this->level = level;
	}
}