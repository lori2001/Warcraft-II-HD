#pragma once
#include "UIElement.h"
#include "Button.h"

namespace ng {
	class Slider : public UIElement {
	public:
		Slider() : UIElement() {
			// create a slider in in position {0, 0}
			Slider slider{ {0, 0} };
			*this = slider;
		}
		Slider(const sf::Vector2f& position):
			Slider(position, NG_TEXTURE_SPTR(DEFAULT_TEXTURE_LOC),
				{ DEFAULT_SHAPE_WIDTH, DEFAULT_SHAPE_HEIGHT },
				{ DEFAULT_ARROW_WIDTH, DEFAULT_ARROW_HEIGHT },
				{ DEFAULT_MARK_WIDTH, DEFAULT_MARK_HEIGHT}) {}
		Slider( const sf::Vector2f& position,
			const ng::TexturePtr texture,
			const sf::Vector2f& shapeSize,
			const sf::Vector2f& arrowSize,
			const sf::Vector2f& markSize,
			const sf::Color& selectColor = sf::Color::White,
			const sf::Vector2f& scale = { 0, 0 })
		{
			setSelectColor(selectColor);
			setSelectThickness(-DEFAULT_SELECT_THICKNESS); // selection goes inside container
			setSizes(shapeSize, arrowSize, markSize);
			setTexture(texture);

			// button has to be centered in order to align properly
			mark_.setOrigin({ mark_.getGlobalBounds().width / 2, mark_.getGlobalBounds().height / 2 });

			setPosition(position);
			setScale(scale);
			
			adjustSliderBox();
			adjustMarkPos();
		}
		// inherits: texture, sizes, selectThickness, selectColor, scale
		Slider(const sf::Vector2f& position, const ng::Slider& sliderWithStyle) :
			Slider(position,
				sliderWithStyle.getTexture(),
				sliderWithStyle.getShapeSize(),
				sliderWithStyle.getArrowSize(),
				sliderWithStyle.getMarkSize(),
				sliderWithStyle.getSelectColor(),
				sliderWithStyle.getScale())
		{
			setSelectColor(sliderWithStyle.getSelectColor());
			setSelectThickness(sliderWithStyle.getSelectThickness());
		}

		void handleEvents(const sf::Event& event, const sf::Vector2f& mouse);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		void setTexture(const ng::TexturePtr texture);
		void setFillColor(const sf::Color& color);
		void setContainerColor(const sf::Color& color) { container_.setFillColor(color); }
		void setMarkColor(const sf::Color& color) { mark_.setFillColor(color); }
		void setArrowsColor(const sf::Color& color);
		void setSliderBox(const sf::FloatRect& sliderBox) { sliderBox_ = sliderBox; }
		void setPosition(const sf::Vector2f& position);
		void setLevel(const float level);
		void setSizes(const sf::Vector2f& shapeSize, const sf::Vector2f& arrowSize, const sf::Vector2f& markSize);
		void setScale(const sf::Vector2f& scale);
		void setSelectColor(const sf::Color& color);
		void setSelectThickness(const float selectSize);
		void setDisabled(const bool isDisabled) { isDisabled_ = isDisabled; }

		const ng::TexturePtr getTexture() const { return texture_; }
		sf::Vector2f getShapeSize() const { return container_.getSize(); }
		sf::Vector2f getArrowSize() const { return leftButton_.getSize(); }
		sf::Vector2f getMarkSize() const { return mark_.getSize(); }
		sf::Color getSelectColor() const { return container_.getOutlineColor(); }
		float getSelectThickness() const { return selectThickness_; }
		float getLevel() const { return level_; }
		sf::Vector2f getSize() const { return { leftButton_.getSize().x + container_.getSize().x + rightButton_.getSize().x, container_.getSize().y }; }
		sf::Vector2f getScale() const { return container_.getScale(); }
		sf::Vector2f getPosition() const { return leftButton_.getPosition(); }
		bool hasChanged() const { return hasChanged_; }
		sf::FloatRect getGlobalBounds() const;
	private:
		// adjust button position based on level
		void adjustMarkPos();
		// set up the mark's virtual box (has some additional offset calibrated for default textures)
		void adjustSliderBox();
	private:
		static constexpr const char* DEFAULT_TEXTURE_LOC = "slider.png";
		static constexpr const float DEFAULT_SHAPE_WIDTH = 300.0F;
		static constexpr const float DEFAULT_SHAPE_HEIGHT = 40.0F;
		static constexpr const float DEFAULT_ARROW_WIDTH = 40.0F;
		static constexpr const float DEFAULT_ARROW_HEIGHT = 40.0F;
		static constexpr const float DEFAULT_MARK_WIDTH = 30.0F;
		static constexpr const float DEFAULT_MARK_HEIGHT = 30.0F;

		ng::TexturePtr texture_;

		sf::FloatRect sliderBox_; // a box for the mark to move in
		sf::RectangleShape container_;
		sf::RectangleShape mark_;
		Button leftButton_; // the button on the left of the window
		Button rightButton_; // the button on the right of the window

		float selectThickness_;
		float level_ = 0; // the output percentage (0 <= level <= 1)

		bool isSliding_ = false; // true if lmb is on hold (then slider is active)
		bool isDisabled_ = false; // if true the object can't be selected or modified
		bool isSelected_ = false; // used for the main section
		bool hasChanged_ = false; // signals to user wheter level has been changed compared to last time
	};
}