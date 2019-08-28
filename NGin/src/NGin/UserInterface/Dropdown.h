#pragma once
#include "UIElement.h"
#include "../Utilities/Align.h"

namespace ngin
{
	class Dropdown : public UIElement
	{
	public:
		Dropdown(const sf::Vector2f& size) : UIElement() {
			setSize(size);

			/*declaration of MANDATORY first element*/
				isSelecteds_.push_back(false);
				drops_.push_back(sf::Text{});
				drops_[0].shape.setSize({ size_.x * 0.85F - 6, size_.y - 6 });

			selectThickness_ = 2.5F; // the thickness of outline when selected
			shapeColor_ = sf::Color::White;
			setCharacterSize(22);
			highlight_.setFillColor(sf::Color(255, 255, 255, 100)); // half-transparent white
		}
		Dropdown() : Dropdown({ 300, 40 }) {}

		void handleEvents(const sf::Event& event, const sf::Vector2f& mouse);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		// creates a dropdown element filled with text
		void addDropString(const sf::String& text);
		// creates a dropdown element filled with a color
		void addDropColor(const sf::Color& color);
		// deletes element with index i
		void deleteDropString(const int i);

		// BEWARE! SETS texture.isRepeated() to true
		void setTexture(sf::Texture& texture);
		void setFont(const sf::Font& font);
		void setFillColor(const sf::Color& color);
		void setTextColor(const sf::Color& color); // sets color to all texts
		void setDropTextColor(const int i, const sf::Color& color);
		void setDropColor(const int i, const sf::Color& color);
		void setSelectColor(const sf::Color& color) { shape_.setOutlineColor(color); }
		void setHighlightColor(const sf::Color& color) { highlight_.setFillColor(color); }
		void setSelectThickness(const float thickness) { selectThickness_ = thickness; }
		void setSize(const sf::Vector2f& size);
		void setScale(const sf::Vector2f& scale);
		void setPosition(const sf::Vector2f& position);
		void setCharacterSize(const unsigned characterSize);
		void setDropString(const int i, const sf::String& text);
		void setDisabled(const bool isDisabled);
		void setStatic(const bool isStatic) { isStatic_ = isStatic; }
		void setActiveDrop(const int i);

		int getActiveDrop() const { return activeDrop; }
		int getDropsNo() const { return int(isSelecteds_.size()); }
		std::string getDropString(const int i) const { return drops_[i].text.getString(); }
		sf::Color getDropColor(const int i) const { return drops_[i].shape.getFillColor(); };
		sf::Vector2f getClosedSize() const { return size_; }
		sf::Vector2f getSize() const { return shape_.getSize(); }
		sf::Vector2f getScale() const { return shape_.getScale(); }
		sf::Vector2f getPosition() const { return shape_.getPosition(); }
		sf::FloatRect getClosedGlobalBounds() const { return closedGlobalBounds_; }

	private:
		sf::Vector2f size_; // the size of the object in closed status
		float selectThickness_; // the size of the outline in pixels

		sf::RectangleShape shape_; // the main shape of the object
		sf::Color shapeColor_; // the color the shape has when not inactive
		sf::RectangleShape highlight_; // the overlay that gets displayed upon currently selected element
		sf::FloatRect closedGlobalBounds_;

		struct TextAndShape {
			TextAndShape(const sf::Text& inText) : TextAndShape() { text = inText; }
			TextAndShape(const sf::RectangleShape& inShape) : TextAndShape() { shape = inShape; }
			TextAndShape() {
				shape.setFillColor(sf::Color::Transparent);
			}
			sf::Text text;
			sf::RectangleShape shape;
		};

		std::vector<TextAndShape> drops_; // texts or shapes inside each element
		unsigned characterSize_;
		std::vector<bool> isSelecteds_; // bool for each element that = true if the element is selected
		bool isActive_; // if true then react - this is done outside of object exept for element nr 0

		int activeDrop = 0; // the number of currently active drop
		bool drawHighlight_ = false; // if true the highlight gets drawn
		bool isDisabled_ = false; // if true the object is unselectable and unactivatable
		bool isStatic_ = false; // if true the values do not ever swap out inside the container
	};
}