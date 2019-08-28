#pragma once
#include "UIElement.h"
#include "../Utilities/Align.h"

namespace ngin {
	class InputText : public UIElement {
	public:
		InputText(const sf::Vector2f& size) {
			cursor_.setFillColor(sf::Color::Transparent);
			cursor_.setString("|");

			setSelectThickness(2.5F);
			setMaxCharacterNo(20);
			setCharacterSize(25);
			setSize(size);
		}
		InputText() : InputText({ 400, 50 }) {}

		void handleEvents(const sf::Event& event, const sf::Vector2f& mouse);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		void setPosition(const sf::Vector2f& position);
		void setString(const sf::String& str);
		void setCharacterSize(const unsigned characterSize);
		void setFont(const sf::Font& font);
		void setFillColor(const sf::Color& color) { shape_.setFillColor(color); }
		void setTextColor(const sf::Color& color) { text_.setFillColor(color); }
		void setTexture(const sf::Texture& texture) { shape_.setTexture(&texture); }
		void setMaxCharacterNo(const unsigned maxCharacterNo) { maxCharacterNo_ = maxCharacterNo; }
		void setSelectColor(const sf::Color& color) { shape_.setOutlineColor(color); }
		void setSelectThickness(const float thickness) { selectThickness_ = thickness; }
		void setSize(const sf::Vector2f& size) { shape_.setSize(size); }
		void setDisabled(const bool isDisabled) { isDisabled_ = isDisabled; }

		sf::String getString() const { return text_.getString(); }
		bool getisActive() const { return isActive_; }
		sf::FloatRect getGlobalBounds() const { return shape_.getGlobalBounds(); }
		sf::Vector2f getPosition() const { return shape_.getPosition(); }

	private:
		sf::RectangleShape shape_; // the block that the text gets displayed in
		float selectThickness_; // the thickness of shape's outline when selected
		unsigned maxCharacterNo_; // holds the number of maximum characters allowed in one object

		sf::Text text_; // the rewritable text inside the rectangle

		sf::Text cursor_; // just a | to show off cursor position
		void adjustCursor();

		bool isActive_ = false; // true whenever writing may occur
		bool isSelected_ = false; // true whenever object is selected by means(ex.mouse)
		bool isDisabled_ = false; // true whenever object canot be selected or changed
	};
}