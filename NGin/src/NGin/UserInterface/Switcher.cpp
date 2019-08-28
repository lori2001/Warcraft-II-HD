#include "Switcher.h"

namespace ngin {
	void Switcher::handleEvents(const sf::Event& event, const sf::Vector2f& mouse)
	{
		if (blockingException_ == -1) {
			hasChanged_ = false;

			button_.handleEvents(event, mouse);

			if (button_.isPressed()) {
				mark_.setTextureRect({
					int(2 * button_.getSize().x + mark_.getSize().x), 0,
					int(mark_.getSize().x), int(mark_.getSize().y) });
			}
			else {
				mark_.setTextureRect({
					int(2 * button_.getSize().x), 0,
					int(mark_.getSize().x), int(mark_.getSize().y) });
			}

			if (button_.isActive()) {
				isActive_ = !isActive_;

				hasChanged_ = true;
			}
			else hasChanged_ = false;
		}
	}
	void Switcher::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(button_);

		if (isActive_)	
			target.draw(mark_);
	}
	void Switcher::setTexture(const sf::Texture& texture)
	{
		button_.setTexture(texture);
		mark_.setTexture(&texture);
	}
	void Switcher::setPosition(const sf::Vector2f& position)
	{
		button_.setPosition(position);
		mark_.setPosition(position);
	}
	void Switcher::setScale(const sf::Vector2f& scale)
	{
		button_.setScale(scale);
		mark_.setScale(scale);
	}
	void Switcher::setButtonSize(const sf::Vector2f& size)
	{
		button_.setSize(size);
	}
	void Switcher::setMarkSize(const sf::Vector2f& size)
	{
		mark_.setSize(size);
	}
	void Switcher::setSize(const sf::Vector2f& size)
	{
		setButtonSize(size);
		setMarkSize(size);
	}
	void Switcher::setFillColor(const sf::Color& color)
	{
		setButtonColor(color);
		setMarkColor(color);
	}
	void Switcher::setMarkColor(const sf::Color& color)
	{
		mark_.setFillColor(color);
	}
	void Switcher::setButtonColor(const sf::Color& color)
	{
		button_.setFillColor(color);
	}
	void Switcher::setSelectColor(const sf::Color& color)
	{
		button_.setSelectColor(color);
	}
	void Switcher::setisActive(const bool active)
	{
		isActive_ = active;
		mark_.setTextureRect({
			int(2 * button_.getSize().x), 0,
			int(mark_.getSize().x), int(mark_.getSize().y) });
	}
	void Switcher::setDisabled(const bool isDisabled)
	{
		button_.setDisabled(isDisabled);
	}
}
