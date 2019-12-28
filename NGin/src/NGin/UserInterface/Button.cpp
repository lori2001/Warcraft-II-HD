#include "Button.h"
#include "Cursor.h"

namespace ngin
{
	void Button::handleEvents(const sf::Event & event, const sf::Vector2f& mouse)
	{
		if (!isDisabled_)
		{
			isActive_ = false;

			// considers mouse to be 1x1 pixels
			if (UIElement::blockingException_ == -1) {
				isSelected_ = shape_.getGlobalBounds().intersects(sf::FloatRect(mouse, { 1,1 }));
			}

			if (isSelected_) {
				shape_.setOutlineThickness(selectThickness_);

				if (event.mouseButton.button == sf::Mouse::Left) {
					if (event.type == sf::Event::MouseButtonPressed)
					{
						isPressed_ = true;

						// audio feedback for pressing
						ngin::Cursor::playSound();

						// create the "pressed in" visual feedback
						shape_.setTextureRect(sf::IntRect{
							 texturePos_.x + static_cast<int>(shape_.getSize().x),
											 static_cast<int>(texturePos_.y),
											 static_cast<int>(shape_.getSize().x),
											 static_cast<int>(shape_.getSize().y)});

						text_.setPosition(sf::Vector2f(textPos_.x + (3 * shape_.getScale().x),
													   textPos_.y + (3 * shape_.getScale().y)));
					}
					else if (isPressed_ && event.type == sf::Event::MouseButtonReleased
						     && blockingException_ == -1)
					{
						isActive_ = true;
					}
				}
			}
			else { // if !isSelected_
				shape_.setOutlineThickness(0);
			}

			// If left mouse button released or unselected...
			if ((event.mouseButton.button == sf::Mouse::Left && event.type == sf::Event::MouseButtonReleased)
				|| !isSelected_)
			{
				isPressed_ = false;

				shape_.setTextureRect(sf::IntRect(texturePos_.x, texturePos_.y, (int)shape_.getSize().x, (int)shape_.getSize().y));
				text_.setPosition(textPos_);
			}
		}
	}
	void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(shape_);
		target.draw(text_);
	}
	void Button::setFont(const sf::Font & font)
	{
		text_.setFont(font);

		// centers text with the new font in mind
		centerTextInShape(text_, shape_);
		textPos_ = text_.getPosition();
	}
	void Button::setTextColor(const sf::Color & color)
	{
		text_.setFillColor(color);
	}
	void Button::setTexture(const sf::Texture & texture)
	{
		shape_.setTexture(&texture);
		shape_.setTextureRect(sf::IntRect(texturePos_.x,
										  texturePos_.y,
										  static_cast<int>(shape_.getSize().x),
										  static_cast<int>(shape_.getSize().y)));
	}
	void Button::setTexturePos(const sf::Vector2i position)
	{
		texturePos_ = position;

		shape_.setTextureRect(sf::IntRect(texturePos_.x,
									      texturePos_.y,
										  static_cast<int>(shape_.getSize().x),
									      static_cast<int>(shape_.getSize().y)));
	}
	void Button::setFillColor(const sf::Color & color)
	{
		shape_.setFillColor(color);
		shapeColor_ = color;
	}
	void Button::setPosition(const sf::Vector2f & position)
	{
		shape_.setPosition(position);

		centerTextInShape(text_, shape_);
		textPos_ = text_.getPosition();
	}
	void Button::setSelectColor(const sf::Color & color)
	{
		shape_.setOutlineColor(color);
	}
	void Button::setSelectThickness(const float thickness)
	{
		selectThickness_ = thickness;
	}
	void Button::setOrigin(const sf::Vector2f& origin) {
		shape_.setOrigin(origin);
		text_.setOrigin(origin);
	}
	void Button::setScale(const sf::Vector2f & scale)
	{
		shape_.setScale(scale);

		text_.setCharacterSize(int(38 * scale.y));

		centerTextInShape(text_, shape_);
		textPos_ = text_.getPosition();
	}
	void Button::setCharacterSize(const unsigned size)
	{
		text_.setCharacterSize(size);
		
		centerTextInShape(text_, shape_);
		textPos_ = text_.getPosition();
	}
	void Button::setSize(const sf::Vector2f size)
	{
		shape_.setSize(size);
	}
	void Button::setDisabled(const bool isDisabled)
	{
		isDisabled_ = isDisabled;

		if (isDisabled) {
			shape_.setFillColor(shapeColor_);
		}
		else if (!isDisabled) {
			isSelected_ = false;
			shape_.setOutlineThickness(0);

			shape_.setFillColor({ 150, 150, 150 });
		}
	}
	void Button::setString(const sf::String & text)
	{
		this->text_.setString(text);

		centerTextInShape(text_, shape_);

		textPos_ = text_.getPosition();
	}
}
