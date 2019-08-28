#include "InputText.h"
#include "../System/Console.h"
#include "Cursor.h"

namespace ngin {
	void InputText::handleEvents(const sf::Event& event, const sf::Vector2f& mouse)
	{
		if (!isDisabled_) {

			isSelected_ = shape_.getGlobalBounds().intersects(sf::FloatRect(mouse, { 1,1 }));

			if (isSelected_)
				shape_.setOutlineThickness(selectThickness_);
			else
				shape_.setOutlineThickness(0);

			// if mouse button pressed on object
			if (isSelected_ && event.mouseButton.button == sf::Mouse::Left && event.type == sf::Event::MouseButtonPressed
				&& blockingException_ == -1)
			{
				ngin::Cursor::playSound();

				// adjusts (|)cursor's position
				adjustCursor();

				// color the cursor character (make visible)
				cursor_.setFillColor(text_.getFillColor());

				isActive_ = true; // makes active so writing may occur
			}
			// if mouse button pressed outside object or enter is pressed
			else if ((!isSelected_ && event.mouseButton.button == sf::Mouse::Left && event.type == sf::Event::MouseButtonPressed)
				|| sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			{
				// make object non-active
				isActive_ = false;

				// hide cursor
				cursor_.setFillColor(sf::Color::Transparent);
			}

			// if active and text was entered
			if (isActive_ && event.type == sf::Event::TextEntered)
			{
				char inputchar = event.text.unicode; // gets the character entered
				std::string container = text_.getString(); // holds the string that's going to be modified

				// if backslash pressed and there are characters
				if (inputchar == '\b') {
					if (container.size() > 0) {
						container.erase(container.end() - 1); // erase the last character
					}
				}
				// if we have less than max characters and it does not go out of bounds
				else if (container.size() < maxCharacterNo_ && text_.getLocalBounds().width < shape_.getGlobalBounds().width - selectThickness_ - 5)
				{
					// if shift is pressed or capslock active make the entered character caps
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
						inputchar = toupper(inputchar);

					// add new character to string
					container += inputchar;
				}

				// add new string to output text
				text_.setString(container);
				// center text
				centerTextInShape(text_, shape_);
				// adjusts cursor's position
				adjustCursor();
			}
		}
	}
	void InputText::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(shape_);
		target.draw(text_);
		target.draw(cursor_);

		// if the font is not set
		if (text_.getFont() == 0) {
			NG_LOG_ONCE_WARN("Font undefined for InputText nr.",
				UIElement::getElementIndex(), " -> OBJECT MAY NOT FUNCTION PROPERLY");
		}
	}
	void InputText::setPosition(const sf::Vector2f& position)
	{
		shape_.setPosition(position);
		centerTextInShape(text_, shape_);
	}
	void InputText::setFont(const sf::Font& font)
	{
		text_.setFont(font);
		cursor_.setFont(font);

		centerTextInShape(text_, shape_);
	}
	void InputText::setString(const sf::String& str)
	{
		text_.setString(str);
		// centers the newly added string
		centerTextInShape(text_, shape_);
	}
	void InputText::setCharacterSize(const unsigned characterSize) {
		text_.setCharacterSize(characterSize);
		centerTextInShape(text_, shape_);

		cursor_.setCharacterSize(characterSize);
	}
	void InputText::adjustCursor()
	{
		// if there is text set cursor after it
		if (text_.getString() != "") {

			cursor_.setPosition({ text_.getGlobalBounds().left + text_.getGlobalBounds().width + 1,
				shape_.getGlobalBounds().top + (shape_.getGlobalBounds().height + selectThickness_) / 2
				- (cursor_.getGlobalBounds().height / 2 + cursor_.getLocalBounds().top) });
		}
		else {
			// if there is no text put the cursor in center of shape
			centerTextInShape(cursor_, shape_);
		}

	}
}