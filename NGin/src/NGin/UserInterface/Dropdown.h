#pragma once
#include "UIElement.h"
#include "../Utilities/Align.h"

namespace ng
{
	class Dropdown : public UIElement
	{
	public:
		Dropdown(const sf::Vector2f& position = {0, 0}) :
			Dropdown(position,
				{ DEFAULT_SHAPE_WIDTH, DEFAULT_SHAPE_HEIGHT },
				NG_TEXTURE_SPTR(DEFAULT_TEXTURE_LOC)) {}
		// inherits: font, textColor, characterSize, highlightColor, selectColor, size, scale, texture
		Dropdown(const Dropdown& dropdownWithStyle, const sf::Vector2f& position = {0, 0}) :
			Dropdown(dropdownWithStyle.getFont(),
				dropdownWithStyle.getTextColor(),
				dropdownWithStyle.getCharacterSize(),
				dropdownWithStyle.getHighlightColor(),
				dropdownWithStyle.getSelectColor(),
				dropdownWithStyle.getSize(),
				dropdownWithStyle.getTexture(),
				position,
				dropdownWithStyle.getScale()) {}
		Dropdown(const ng::FontPtr font,
			const sf::Color& textColor,
			const unsigned characterSize,
			const sf::Color& highlightColor,
			const sf::Color& selectColor,
			const sf::Vector2f& size,
			const ng::TexturePtr texture,
			const sf::Vector2f& position = { 0, 0 },
			const sf::Vector2f& scale = { 1, 1 }) :
			Dropdown(position, size, texture)
		{
			setFont(font);
			setTextColor(textColor);
			setCharacterSize(characterSize);
			setHighlightColor(highlightColor);
			setSelectColor(selectColor);
			setSize(size);
			setScale(scale);
		}
		Dropdown(const sf::Vector2f& position,
			const sf::Vector2f& size,
			const ng::TexturePtr texture) : UIElement() {

			// --- declaration of MANDATORY first element --------
			isSelecteds_.push_back(false);
			drops_.push_back(TextAndShape{});
			drops_[0].shape.setSize({ size_.x * 0.85F - 6, size_.y - 6 });

			setSize(size);
			setTexture(texture);
			setPosition(position);
			setSelectThickness(DEFAULT_SELECT_THICKNESS);

			shapeColor_ = sf::Color::White;
			highlight_.setFillColor({
				DEFAULT_HIGHLIGHT_COLOR_R,
				DEFAULT_HIGHLIGHT_COLOR_G,
				DEFAULT_HIGHLIGHT_COLOR_B,
				DEFAULT_HIGHLIGHT_COLOR_A });

			setCharacterSize(DEFAULT_CHAR_SIZE);
		}

		void handleEvents(const sf::Event& event, const sf::Vector2f& mouse);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		// creates a dropdown element filled with string
		void addDropString(const std::string& string);
		// creates a dropdown element with given text properties
		// ! changes its position property
		void addDropText(const sf::Text& text);
		// clears all previous drops and sets it to <vector> of texts
		void setDropTextVec(const std::vector<sf::Text>& textVector);
		// creates a dropdown element filled with a color
		void addDropColor(const sf::Color& color);

		void setDropTextColor(const int i, const sf::Color& color);
		void setDropColor(const int i, const sf::Color& color);
		void setDropString(const int i, const std::string& text);

		// deletes drop element with index i
		void deleteDrop(const int i);
		
		// deletes all drops
		void deleteDrops();

		// BEWARE! SETS texture.isRepeated() to true
		void setTexture(const ng::TexturePtr texture);
		void setFillColor(const sf::Color& color);
		void setSelectThickness(const float thickness) { selectThickness_ = thickness; }
		void setSelectColor(const sf::Color& color) { shape_.setOutlineColor(color); }
		void setHighlightColor(const sf::Color& color) { highlight_.setFillColor(color); }
		void setSize(const sf::Vector2f& size);
		void setScale(const sf::Vector2f& scale);
		void setPosition(const sf::Vector2f& position);
		void setDisabled(const bool isDisabled);
		void setStatic(const bool isStatic) { isStatic_ = isStatic; }
		void setActiveDrop(const int i);
		
		void setFont(const ng::FontPtr font);
		void setTextColor(const sf::Color& color);
		void setCharacterSize(const unsigned characterSize);

		// returns true if dropped down
		bool isActive() { return isActive_; }
		bool hasChanged() { return wasActive_ != isActive_; }

		ng::TexturePtr getTexture() const { return texture_; }
		ng::FontPtr getFont() const { return font_; }
		int getActiveDrop() const { return activeDrop_; }
		int getDropsNo() const { return int(isSelecteds_.size()); }
		unsigned getCharacterSize() const { return drops_[0].text.getCharacterSize(); }
		sf::Color getTextColor() const { return drops_[0].text.getFillColor(); }
		std::string getDropString(const int i) const { return drops_[i].text.getString(); }
		sf::Color getDropColor(const int i) const { return drops_[i].shape.getFillColor(); };
		sf::Color getHighlightColor() const { return highlight_.getFillColor(); }
		sf::Color getSelectColor() const { return shape_.getOutlineColor(); }
		sf::Vector2f getClosedSize() const { return size_; }
		sf::Vector2f getSize() const { return shape_.getSize(); }
		sf::Vector2f getScale() const { return shape_.getScale(); }
		sf::Vector2f getPosition() const { return shape_.getPosition(); }
		sf::FloatRect getClosedGlobalBounds() const { return closedGlobalBounds_; }
		sf::FloatRect getGlobalBounds() const { return shape_.getGlobalBounds(); }
	
	private:
		static constexpr const char* DEFAULT_TEXTURE_LOC = "dropdown.png";
		static constexpr const float DEFAULT_SHAPE_WIDTH = 300.0F;
		static constexpr const float DEFAULT_SHAPE_HEIGHT = 40.0F;

		static constexpr int DEFAULT_HIGHLIGHT_COLOR_R = 255;
		static constexpr int DEFAULT_HIGHLIGHT_COLOR_G = 255;
		static constexpr int DEFAULT_HIGHLIGHT_COLOR_B = 255;
		static constexpr int DEFAULT_HIGHLIGHT_COLOR_A = 100;

		ng::TexturePtr texture_;
		ng::FontPtr font_;

		sf::FloatRect closedGlobalBounds_; // the main rectangle representing the closed selectable area (global, scaled)
		sf::Vector2f size_; // the size of the object in closed status (local, unscaled)
		float selectThickness_; // the size of the outline in pixels

		sf::RectangleShape shape_; // the main shape of the object
		sf::Color shapeColor_; // the color the shape has when not disabled
		sf::RectangleShape highlight_; // the overlay that gets displayed upon currently selected element

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
		bool isActive_ = false; // if true then react - this is done outside of object exept for element nr 0
		bool wasActive_ = false; // measures change in isActive

		int activeDrop_ = 0; // the number of currently active drop
		bool drawHighlight_ = false; // if true the highlight gets drawn
		bool isDisabled_ = false; // if true the object is unselectable and unactivatable
		bool isStatic_ = false; // if true the values do not ever swap out inside the container
	};
}