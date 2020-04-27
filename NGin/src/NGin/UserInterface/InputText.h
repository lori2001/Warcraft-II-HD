#pragma once
#include "UIElement.h"
#include "../Utilities/Align.h"

namespace ng {
	class InputText : public UIElement {
	public:
		InputText(
			const ng::TexturePtr texture = NG_TEXTURE_SPTR(DEFAULT_TEXTURE_LOC),
			const sf::Vector2f size = { DEFAULT_SHAPE_WIDTH, DEFAULT_SHAPE_HEIGHT},
			const ng::FontPtr font = NG_FONT_SPTR(DEFAULT_FONT_LOC),
			const sf::Color textColor = sf::Color::White,
			const sf::Color selectColor = sf::Color::White,
			const float selectThickness = DEFAULT_SELECT_THICKNESS,
			const unsigned fontSize =  DEFAULT_CHAR_SIZE,
			const sf::Vector2f position = { 0, 0 }) : UIElement()
		{
			cursor_.setFillColor(sf::Color::Transparent);
			cursor_.setString("|");

			setSelectThickness(selectThickness);
			setMaxCharacterNo(20);
			setCharacterSize(25);
			setSize(size);

			setTexture(texture);
			setSize(size);
			setFont(font);
			setTextColor(textColor);
			setSelectColor(selectColor);
			setCharacterSize(fontSize);
			setPosition(position);
		}
		InputText(
			const InputText& inputTextWithStyle,
			const sf::Vector2f position = { 0, 0 }
		) : InputText(
			inputTextWithStyle.getTexture(),
			inputTextWithStyle.getSize(),
			inputTextWithStyle.getFont(),
			inputTextWithStyle.getTextColor(),
			inputTextWithStyle.getSelectColor(),
			inputTextWithStyle.getSelectThickness(),
			inputTextWithStyle.getCharacterSize(),
			position) {}

		void handleEvents(const sf::Event& event, const sf::Vector2f& mouse);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		void setPosition(const sf::Vector2f& position);
		void setString(const sf::String& str);
		void setCharacterSize(const unsigned characterSize);
		void setFont(const ng::FontPtr font);
		void setFillColor(const sf::Color& color) { shape_.setFillColor(color); }
		void setTextColor(const sf::Color& color) { text_.setFillColor(color); }
		void setTexture(const ng::TexturePtr texture) { texture_ = texture; shape_.setTexture(&*texture_); }
		void setMaxCharacterNo(const unsigned maxCharacterNo) { maxCharacterNo_ = maxCharacterNo; }
		void setSelectColor(const sf::Color& color) { shape_.setOutlineColor(color); }
		void setSelectThickness(const float thickness) { selectThickness_ = thickness; }
		void setSize(const sf::Vector2f& size) { shape_.setSize(size); }
		void setDisabled(const bool isDisabled) { isDisabled_ = isDisabled; }

		sf::String getString() const { return text_.getString(); }
		bool getIsActive() const { return isActive_; }
		sf::FloatRect getGlobalBounds() const { return shape_.getGlobalBounds(); }
		sf::Vector2f getPosition() const { return shape_.getPosition(); }
		sf::Vector2f getSize() const { return shape_.getSize(); }
		ng::TexturePtr getTexture() const { return texture_; }
		ng::FontPtr getFont() const { return font_; }
		sf::Color getTextColor() const { return text_.getFillColor(); }
		sf::Color getSelectColor() const { return shape_.getOutlineColor(); }
		unsigned getCharacterSize() const { return text_.getCharacterSize(); }
		float getSelectThickness() const { return selectThickness_; }
		unsigned getMaxCharacterNum() const { return maxCharacterNo_; }

	private:
		static constexpr auto DEFAULT_TEXTURE_LOC = "inputtext.png";
		static constexpr const float DEFAULT_SHAPE_WIDTH = 400;
		static constexpr const float DEFAULT_SHAPE_HEIGHT = 50;

		ng::FontPtr font_;
		ng::TexturePtr texture_;

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