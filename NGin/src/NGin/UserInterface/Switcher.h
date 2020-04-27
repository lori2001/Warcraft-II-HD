#pragma once
#include "UIElement.h"

#include "../System/Resources.h"
#include "Button.h"

namespace ng {
	class Switcher : public UIElement {
	public:
		Switcher(const sf::Vector2f& position,
			const sf::Vector2f& size,
			const ng::TexturePtr texture) : Switcher(size, size, texture, position){}
		Switcher( const sf::Vector2f& buttonSize = { DEFAULT_BUTTON_WIDTH, DEFAULT_BUTTON_HEIGHT },
			const sf::Vector2f& markSize = { DEFAULT_MARK_WIDTH, DEFAULT_MARK_HEIGHT },
			const ng::TexturePtr texture = NG_TEXTURE_SPTR(DEFAULT_TEXTURE_LOC),
			const sf::Vector2f& position = { 0, 0 },
			const sf::Vector2f& switcherScale = { 1, 1 },
			const sf::Color& selectColor = sf::Color::White,
			const float selectThickness = DEFAULT_SELECT_THICKNESS) : UIElement()
		{
			setButtonSize(buttonSize);
			setMarkSize(markSize);
			setPosition(position);
			setScale(switcherScale);
			setSelectColor(selectColor);
			setTexture(texture);
		}
		// inherits switcher properties:
		// button size, mark size, texture, scale, select thickness, select color
		Switcher(const Switcher& switcher, const sf::Vector2f& position = {0, 0}) :
			Switcher(
				switcher.getButtonSize(),
				switcher.getMarkSize(),
				switcher.getTexture(),
				position,
				switcher.getScale(),
				switcher.getSelectColor(),
				switcher.getSelectThickness() )
		{}

		void handleEvents(const sf::Event& event, const sf::Vector2f& mouse);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		void setTexture(const ng::TexturePtr texture);
		void setPosition(const sf::Vector2f& position);
		void setScale(const sf::Vector2f& scale);
		void setButtonSize(const sf::Vector2f& size);
		void setMarkSize(const sf::Vector2f& size);
		void setSize(const sf::Vector2f& size);
		void setFillColor(const sf::Color& color);
		void setMarkColor(const sf::Color& color);
		void setButtonColor(const sf::Color& color);
		void setSelectColor(const sf::Color& color);
		void setSelectThickness(const float thickness);
		void setIsActive(const bool active);
		void setDisabled(const bool isDisabled);

		bool isActive() const { return isActive_; }
		bool hasChanged() const { return hasChanged_; }
		sf::Vector2f getButtonSize() const { return button_.getSize(); }
		sf::Vector2f getMarkSize() const { return mark_.getSize(); }
		sf::Vector2f getSize() const { return button_.getSize(); }
		sf::Vector2f getPosition() const { return button_.getPosition(); }
		sf::Vector2f getScale() const { return button_.getScale(); }
		sf::Color getSelectColor() const { return button_.getSelectColor(); }
		float getSelectThickness() const { return button_.getSelectThickness(); }
		ng::TexturePtr getTexture() const { return texture_; }
		sf::FloatRect getGlobalBounds() const { return button_.getGlobalBounds(); }
	private:
		static constexpr const char* DEFAULT_TEXTURE_LOC = "switcher.png";
		static constexpr const float DEFAULT_BUTTON_WIDTH = 60.0F;
		static constexpr const float DEFAULT_BUTTON_HEIGHT = 60.0F;
		static constexpr const float DEFAULT_MARK_WIDTH = 60.0F;
		static constexpr const float DEFAULT_MARK_HEIGHT = 60.0F;
		
		ng::TexturePtr texture_;

		Button button_;
		sf::RectangleShape mark_;

		bool isActive_ = false;
		bool hasChanged_ = false;
	};
}