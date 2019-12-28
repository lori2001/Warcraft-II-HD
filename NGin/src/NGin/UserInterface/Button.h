#pragma once
#include "UIElement.h"
#include "../Utilities/Align.h"

namespace ngin
{
	class Button : public UIElement
	{
	public:
		Button(const sf::Vector2f& size) {
			shape_.setSize(size);
			selectThickness_ = 3.499F;
		}
		Button(const sf::Vector2f& size, const sf::Texture& texture) : Button(size) {
			this->setTexture(texture);
		}
		Button(const sf::Font& font, const sf::String& txt, const sf::Vector2f& buttonSize) : Button(buttonSize)
		{
			text_.setFont(font);
			text_.setString(txt);
			text_.setCharacterSize(30);

			centerTextInShape(text_, shape_);
			textPos_ = text_.getPosition();
		}
		Button() : Button(sf::Vector2f{ 400, 50 }) {}
		Button(const sf::String& txt, const sf::Vector2f& buttonSize) : Button(buttonSize)
		{
			text_.setString(txt);
			text_.setCharacterSize(30);
		}
		// Handles input events and plays given sounds and animations whenever needed.
		void handleEvents(const sf::Event& event, const sf::Vector2f& mouse);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		void setFont(const sf::Font& font);
		void setTextColor(const sf::Color& color);
		void setString(const sf::String& text);
		void setTexture(const sf::Texture& texture);
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

		sf::Vector2f getScale() const { return shape_.getScale(); }
		sf::Vector2f getPosition() const { return shape_.getPosition(); }
		sf::Vector2f getSize() const { return shape_.getSize(); }
		sf::FloatRect getGlobalBounds() const { return shape_.getGlobalBounds(); }
		bool isPressed() const { return isPressed_; }
		bool isActive() const { return isActive_; }
	private:
		sf::RectangleShape shape_;

		sf::Text text_;

		float selectThickness_;
		sf::Vector2f textPos_;
		sf::Vector2i texturePos_ = {0, 0}; // the position at which textures should be loaded from

		sf::Color shapeColor_;
		bool isDisabled_ = false;
		bool isPressed_ = false;
		bool isSelected_ = false;
		bool isActive_ = false;
	};
}
