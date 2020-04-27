#include "Button.h"
#include "Cursor.h"

#include "../System/Console.h"

namespace ng
{
	void Button::handleEvents(const sf::Event & event, const sf::Vector2f& mouse)
	{
		if (state_ != STATES::DISABLED )
		{
			if ((UIElement::blockingException_ == -1 || blockingException_ == getUIElementIndex())
				&& shape_.getGlobalBounds().contains(mouse))
			{
				if(state_ != STATES::PRESSED)
					state_ = STATES::SELECTED;
			}
			else if (state_ != STATES::UNSELECTED) // if !SELECTED
			{
				state_ = STATES::UNSELECTED;

				shape_.setOutlineThickness(0);
				setTexturePos(texturePos_);
				text_.setPosition(textPos_);
			}

			if (state_ == STATES::SELECTED)
			{
				shape_.setOutlineThickness(selectThickness_);

				if (event.mouseButton.button == sf::Mouse::Left) {
					if (event.type == sf::Event::MouseButtonPressed && state_ != STATES::PRESSED)
					{
						state_ = STATES::PRESSED;

						// audio feedback for pressing
						ng::Cursor::playSound();

						// create the "pressed in" visual feedback
						shape_.setTextureRect(sf::IntRect{
						static_cast<int>(texturePos_.x) + static_cast<int>(shape_.getSize().x),
						static_cast<int>(texturePos_.y),
						static_cast<int>(shape_.getSize().x),
						static_cast<int>(shape_.getSize().y)});

						text_.setPosition(sf::Vector2f(textPos_.x + (3 * shape_.getScale().x),
													   textPos_.y + (3 * shape_.getScale().y)));
					}
				}
			}
			// If left mouse button released after pressed...
			if ((event.mouseButton.button == sf::Mouse::Left && event.type == sf::Event::MouseButtonReleased)
				&& state_ == STATES::PRESSED)
			{
				state_ = STATES::ACTIVE;

				setTexturePos(texturePos_);
				text_.setPosition(textPos_);
			}
		}
	}
	void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(shape_);
		target.draw(text_);
	}
	void Button::setFont(const ng::FontPtr font)
	{
		font_ = font;
		text_.setFont(*font_);

		// centers text with the new font in mind
		centerTextInShape(text_, shape_);
		textPos_ = text_.getPosition();
	}
	void Button::setTextColor(const sf::Color & color)
	{
		text_.setFillColor(color);
	}
	void Button::setTexture(const ng::TexturePtr texture)
	{
		texture_ = texture;

		shape_.setTexture(&*texture_);
		setTexturePos(texturePos_);
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

		if (isDisabled) {
			state_ = STATES::DISABLED;
			shape_.setFillColor(shapeColor_);
		}
		else if (!isDisabled) {
			state_ = STATES::NONE;
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
