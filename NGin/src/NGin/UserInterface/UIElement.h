#pragma once
#include <vector>
#include "SFML/Graphics.hpp"

namespace ngin
{
	// holds every class that all UIElements should have in common
	class UIElement : public sf::Drawable
	{
	public:
		virtual void handleEvents(const sf::Event& event, const sf::Vector2f& mouse) = 0;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
		virtual void setPosition(const sf::Vector2f& position) = 0;
		virtual sf::Vector2f getPosition() const = 0;

		int getElementIndex() const {
			auto it = std::find(Elements_.begin(), Elements_.end(), elementNo_);
			return std::distance(Elements_.begin(), it);;
		}

	public:
		UIElement() {
			elementNo_ = static_cast<int>(Elements_.size());
			Elements_.push_back(elementNo_);
		}
		UIElement(const UIElement&) { // for containers (vectors)
			elementNo_ = static_cast<int>(Elements_.size());
			Elements_.push_back(elementNo_);
		}
		virtual ~UIElement()
		{
			auto it = std::find(Elements_.begin(), Elements_.end(), elementNo_);
			Elements_.erase(it);
		}

	protected:
		// blocks the simultaneous pressing of different overlapping UIElements
		// by holding the only exception to it (-1 means none)
		static int blockingException_;
	
	private:
		// helps count number of UIElements for debugging purposes
		static std::vector<size_t> Elements_;
		// NOT INDEX (NOT IN ORDER)
		size_t elementNo_;
	};
}
