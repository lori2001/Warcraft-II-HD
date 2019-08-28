#include "Slider.h"
#include "../System/Console.h"
#include "Cursor.h"

namespace ngin {
	void Slider::handleEvents(const sf::Event& event, const sf::Vector2f& mouse)
	{
		hasChanged_ = false; // the level has not yet changed in this frame

		if (!isDisabled_) {
			isSelected_ = container_.getGlobalBounds().intersects({ mouse, { 1,1 } });

			if (isSelected_) {
				container_.setOutlineThickness(selectThickness_);

				if (event.mouseButton.button == sf::Mouse::Left && event.type == sf::Event::MouseButtonPressed
					&& blockingException_ == -1) {
					// isSliding is true if isSelected and while lmb is held 
					isSliding_ = true;

					// play slider sound
					ngin::Cursor::playSound();
				}
			}
			else
				container_.setOutlineThickness(0);

			if (event.type == sf::Event::MouseButtonReleased && isSliding_) {

				// if lmb is released set to false
				isSliding_ = false;
			}
			else if (isSliding_) {
				// calculate the level based on the mouse's position (OUTPUT: a number between 0 and 1)
				level_ = (mouse.x - sliderBox_.left) / sliderBox_.width;

				// Safely restrict that number
				if (level_ > 1) level_ = 1;
				else if (level_ < 0) level_ = 0;

				hasChanged_ = true; // signal that the level has changed in this frame

				adjustMarkPos();
			}

			leftButton_.handleEvents(event, mouse);
			rightButton_.handleEvents(event, mouse);

			if (leftButton_.isActive() && blockingException_ == -1) {
				float temp = level_ - 0.05F; // step down level by 0.05

				// establish 0 as minimum limit
				if (temp < 0) level_ = 0;
				else level_ = temp;

				hasChanged_ = true; // signal that the level has changed in this frame
				adjustMarkPos();
			}
			else if (rightButton_.isActive() && blockingException_ == -1) {
				float temp = level_ + 0.05F; // step up level by 0.05

				// establish 1 as maximum limit
				if (temp > 1) level_ = 1;
				else level_ = temp;

				hasChanged_ = true; // signal that the level has changed in this frame
				adjustMarkPos();
			}
		}
	}
	void Slider::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(container_);
		target.draw(leftButton_);
		target.draw(rightButton_);
		target.draw(mark_);
	}
	void Slider::setTexture(const sf::Texture& texture)
	{
		container_.setTexture(&texture);
		leftButton_.setTexture(texture);
		rightButton_.setTexture(texture);
		mark_.setTexture(&texture);

		leftButton_.setTexturePos({ 0, 0 });

		container_.setTextureRect({ 2 * (int)leftButton_.getSize().x, 0, (int)container_.getSize().x, (int)container_.getSize().y });

		rightButton_.setTexturePos({ 2 * int(leftButton_.getSize().x) + int(container_.getSize().x), 0 });

		mark_.setTextureRect ({
			int(container_.getSize().x) + 2 * int(leftButton_.getSize().x) + 2 * int(rightButton_.getSize().x), 0,
			(int)mark_.getSize().x, (int)mark_.getSize().y
		});
	}
	void Slider::setFillColor(const sf::Color& color)
	{
		setContainerColor(color);
		setMarkColor(color);
		setArrowsColor(color);
	}
	void Slider::setArrowsColor(const sf::Color& color)
	{
		leftButton_.setFillColor(color);
		rightButton_.setFillColor(color);
	}
	void Slider::setPosition(const sf::Vector2f& position)
	{
		// positon structure (leftArrow->shape->rightArrow)
		leftButton_.setPosition(position);
		container_.setPosition({ leftButton_.getGlobalBounds().left + leftButton_.getGlobalBounds().width, position.y });
		rightButton_.setPosition({ container_.getGlobalBounds().left + container_.getGlobalBounds().width, position.y });

		// put the mark where it should be
		adjustSliderBox();
		adjustMarkPos();
	}
	void Slider::setLevel(const float level)
	{
		// only if the level wasn't changed manually
		if (!hasChanged_) {

			// check if the set level is valid
			if (level > 1) {
				NG_LOG_ONCE_WARN("Element: ", getElementIndex(),
					" Slider level set to: ", level, " -> above 1(100%)!");
			}
			else if (level < 0) {
				NG_LOG_ONCE_WARN("Element: ", getElementIndex(),
					" Slider level set to: ", level, " -> below 0(0%)!");
			}

			// set level
			level_ = level;
			// adjust mark position to level
			adjustMarkPos();
		}

		hasChanged_ = false;
	}
	void Slider::setSizes(const sf::Vector2f& shapeSize, const sf::Vector2f& arrowSize, const sf::Vector2f& markSize)
	{
		container_.setSize(shapeSize);
		leftButton_.setSize(arrowSize);
		rightButton_.setSize(arrowSize);
		mark_.setSize(markSize);

		adjustSliderBox();
	}
	void Slider::setScale(const sf::Vector2f& scale)
	{
		container_  .setScale(scale);
		leftButton_ .setScale(scale);
		rightButton_.setScale(scale);
		mark_       .setScale(scale);

		adjustSliderBox();
	}
	void Slider::setSelectColor(const sf::Color& color)
	{
		container_.setOutlineColor(color);
		leftButton_.setSelectColor(color);
		rightButton_.setSelectColor(color);
	}
	void Slider::setSelectThickness(const float selectSize)
	{
		selectThickness_ = selectSize;
		leftButton_.setSelectThickness(selectSize);
		rightButton_.setSelectThickness(selectSize);
	}
	sf::FloatRect Slider::getGlobalBounds() const
	{
		// widths add up
		float width = leftButton_.getGlobalBounds().width
					+ container_.getGlobalBounds().width
					+ rightButton_.getGlobalBounds().width;

		// biggest of heights
		float height = container_.getGlobalBounds().height;
		if (height < leftButton_ .getGlobalBounds().height)
			height = leftButton_ .getGlobalBounds().height;
		if (height < rightButton_.getGlobalBounds().height)
			height = rightButton_.getGlobalBounds().height;

		return sf::FloatRect{
			leftButton_.getGlobalBounds().left, leftButton_.getGlobalBounds().top,
			width, height };
	}
	void Slider::adjustMarkPos()
	{
		mark_.setPosition({
			sliderBox_.left + sliderBox_.width * level_,
			sliderBox_.top + sliderBox_.height / 2});
	}
	void Slider::adjustSliderBox()
	{
		float left = container_.getGlobalBounds().left + container_.getOutlineThickness()
			+ mark_.getGlobalBounds().width / 2 + 5;
		float top = container_.getGlobalBounds().top + container_.getOutlineThickness();
		float width = container_.getGlobalBounds().width - mark_.getGlobalBounds().width - 10;
		float height = container_.getGlobalBounds().height;

		sliderBox_ = { left, top, width, height };
	}
}