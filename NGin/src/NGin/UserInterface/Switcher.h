#pragma once
#include "UIElement.h"
#include "Button.h"

namespace ngin {
	class Switcher : public UIElement {
	public:
		Switcher() : Switcher(sf::Vector2f{ 60,60 }) {}
		Switcher(const sf::Vector2f& size) : Switcher(size, size) {}
		Switcher(const sf::Vector2f& buttonSize, const sf::Vector2f& markSize ) {
			setButtonSize(buttonSize);
			setMarkSize(markSize);
		}

		void handleEvents(const sf::Event& event, const sf::Vector2f& mouse);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		void setTexture(const sf::Texture& texture);
		void setPosition(const sf::Vector2f& position);
		void setScale(const sf::Vector2f& scale);
		void setButtonSize(const sf::Vector2f& size);
		void setMarkSize(const sf::Vector2f& size);
		void setSize(const sf::Vector2f& size);
		void setFillColor(const sf::Color& color);
		void setMarkColor(const sf::Color& color);
		void setButtonColor(const sf::Color& color);
		void setSelectColor(const sf::Color& color);
		void setisActive(const bool active);
		void setDisabled(const bool isDisabled);

		bool isActive() const { return isActive_; }
		bool hasChanged() const { return hasChanged_; }
		sf::Vector2f getSize() const { return button_.getSize(); }
		sf::Vector2f getPosition() const { return button_.getPosition(); }
		sf::FloatRect getGlobalBounds() const { return button_.getGlobalBounds(); }
	private:
		sf::RectangleShape mark_;

		Button button_;

		bool isActive_ = false;
		bool hasChanged_ = false;
	};
}