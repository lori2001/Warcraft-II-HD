#pragma once
#include <vector>
#include "SFML/Graphics.hpp"
#include "../System/Resources.h"

namespace ng
{
	// holds every class that all UIElements should have in common
	class UIElement : public sf::Drawable
	{
	public:
		virtual void handleEvents(const sf::Event& event, const sf::Vector2f& mouse) = 0;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

		virtual void setPosition(const sf::Vector2f& position) = 0;

		virtual sf::Vector2f getPosition() const = 0;
		virtual sf::FloatRect getGlobalBounds() const = 0;

		int getUIElementIndex() const {
			auto it = std::find(elements_.begin(), elements_.end(), elementNo_);
			return std::distance(elements_.begin(), it);;
		}

		// returns true if one ui element took blocking exception
		// privileges (ex. dropdown is dropped down somewhere)
		static bool hasBlockingException() {
			return blockingException_ != -1;
		}

	public:
		UIElement() {
			elementNo_ = static_cast<int>(elements_.size());
			elements_.push_back(elementNo_);
		}
		UIElement(const UIElement&) { // for containers (vectors)
			elementNo_ = static_cast<int>(elements_.size());
			elements_.push_back(elementNo_);
		}
		virtual ~UIElement()
		{
			auto it = std::find(elements_.begin(), elements_.end(), elementNo_);

			if(it != elements_.end())
				elements_.erase(it);
		}

	protected:
		// blocks the simultaneous pressing of different overlapping UIElements
		// by holding the only exception to it (-1 means none)
		static int blockingException_;

		enum class CONSTRUCTOR {
			MINIMAL
		};

		static constexpr const char* DEFAULT_FONT_LOC = "font.ttf";
		static constexpr const unsigned DEFAULT_CHAR_SIZE = 30;
		static constexpr const float DEFAULT_SELECT_THICKNESS = 2.5F;
	private:
		// helps count number of UIElements for debugging purposes
		static std::vector<size_t> elements_;
		// NOT INDEX (NOT IN ORDER)
		size_t elementNo_;
	};
}
