#pragma once
#include "UIElement.h"
#include "../Utilities/Align.h"

namespace ng
{
	class Button : public UIElement
	{
	public:
		Button(const sf::Vector2f& size, const ng::TexturePtr texture) : Button() {
			setSize(size);
			setTexture(texture);
		}
		Button(const sf::String& string, const ng::FontPtr font) : Button()
		{
			setFont(font);
			setString(string);
		}
		Button(const sf::String& string, const ng::FontPtr font,
			const sf::Vector2f& buttonSize, const ng::TexturePtr texture) : Button()
		{
			setSize(buttonSize);
			setString(string);
			setTexture(texture);
		}
		Button(
			const ng::FontPtr font,
			const sf::String& string,
			const unsigned characterSize,
			const sf::Color& fontColor,
			const sf::Vector2f& buttonSize,
			const ng::TexturePtr buttonTexture,
			const sf::Color& selectColor,
			const sf::Vector2f& position = {0, 0},
			const sf::Vector2f& scale = {1.0F, 1.0F}) : Button()
		{
			setFont(font);
			setCharacterSize(characterSize);
			setTextColor(fontColor);
			setSize(buttonSize);
			setTexture(buttonTexture);
			setSelectColor(selectColor);
			setString(string);
			setScale(scale);
			setPosition(position);
		}
		// copies a button's style / changes position and string
		// inherits: font, characterSize, textColor, size, scale, texture, selectColor, selectThickness
		Button(const sf::String string, const ng::Button& buttonWithStyle, const sf::Vector2f position = {0, 0})
			: Button()
		{
			setFont(buttonWithStyle.getFont());
			setCharacterSize(buttonWithStyle.getCharacterSize());
			setTextColor(buttonWithStyle.getFontColor());
			setSize(buttonWithStyle.getSize());
			setScale(buttonWithStyle.getScale());
			setTexture(buttonWithStyle.getTexture());
			setSelectColor(buttonWithStyle.getSelectColor());
			setSelectThickness(buttonWithStyle.getSelectThickness());
			setString(string);
			setPosition(position);
		}
		Button(const sf::String& string) :
			Button(string, NG_FONT_SPTR(DEFAULT_FONT_LOC), { DEFAULT_WIDTH, DEFAULT_HEIGHT }, NG_TEXTURE_SPTR(DEFAULT_TEXTURE_LOC)) {}
		Button() : UIElement() {
			setCharacterSize(DEFAULT_CHAR_SIZE);
			setSelectThickness(DEFAULT_SELECT_THICKNESS);
		}

		// Handles input events and plays given sounds and animations whenever needed.
		void handleEvents(const sf::Event& event, const sf::Vector2f& mouse);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		void setFont(const ng::FontPtr font);
		void setTextColor(const sf::Color& color);
		void setString(const sf::String& text);
		void setTexture(const ng::TexturePtr texture);
		void setTexturePos(const sf::Vector2i position);
		void setFillColor(const sf::Color& color);
		void setPosition(const sf::Vector2f& position);
		void setSelectColor(const sf::Color& color);
		void setSelectThickness(const float thickness);
		void setOrigin(const sf::Vector2f& origin);
		void setScale(const sf::Vector2f& scale);
		void setCharacterSize(const unsigned size);
		void setSize(const sf::Vector2f size);
		void setDisabled(const bool isDisabled);

		const ng::TexturePtr getTexture() const { return texture_;; }
		sf::Vector2f getScale() const { return shape_.getScale(); }
		const ng::FontPtr getFont() const { return font_; }
		unsigned getCharacterSize() const { return text_.getCharacterSize(); }
		sf::Color getFontColor() const { return text_.getFillColor(); }
		sf::Vector2f getPosition() const { return shape_.getPosition(); }
		sf::Vector2f getSize() const { return shape_.getSize(); }
		sf::Color getSelectColor() const { return shape_.getOutlineColor(); }
		float getSelectThickness() const { return selectThickness_; }
		sf::FloatRect getGlobalBounds() const { return shape_.getGlobalBounds(); }

		bool isPressed() const { return state_ == STATES::PRESSED; }
		bool isActive() const { return state_ == STATES::ACTIVE; }
	private:
		static constexpr const char* DEFAULT_TEXTURE_LOC = "button.png";
		static constexpr const int DEFAULT_WIDTH = 400;
		static constexpr const int DEFAULT_HEIGHT = 50;

		ng::TexturePtr texture_;
		ng::FontPtr font_;

		sf::RectangleShape shape_;

		sf::Text text_;

		float selectThickness_;
		sf::Vector2f textPos_;
		sf::Vector2i texturePos_ = { 0, 0 }; // the position at which textures should be loaded from

		sf::Color shapeColor_;

		enum class STATES {
			NONE = 0,
			DISABLED,
			SELECTED,
			PRESSED,
			ACTIVE,
			UNSELECTED,
		} state_;
	};
}
