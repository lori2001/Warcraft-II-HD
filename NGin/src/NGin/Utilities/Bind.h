#pragma once
#include "SFML/Graphics.hpp"
#include "../UserInterface/UIElement.h"
#include <unordered_map>

namespace ngin {
	class Bindables {
	public:
		// sets up an object which other objects can be binded to
		static void create(const std::string key, const sf::Vector2f& positionOfBindable);
		
		// intended for internal use only
		// Object with property 'position' moves after bindable object
		// returns true if successful
		// returns false if unsuccessful
		static bool bindPosition(sf::Vector2f& position,
			const std::string& keyOfBindable,
			const sf::Vector2f& positionOfBindable);

		// void bindScale();
		// void bindRotation();

	// OVERLOADS
	public:
		static bool bindPosition(sf::RectangleShape& rect,
			const std::string& keyOfBindable,
			const sf::Vector2f& positionOfBindable)
		{
			sf::Vector2f position = rect.getPosition();
			if (bindPosition(position, keyOfBindable, positionOfBindable)) {
				rect.setPosition(position);
				return true;
			}
			else return false;
		}
		static bool bindPosition(sf::Sprite& sprite,
			const std::string& keyOfBindable,
			const sf::Vector2f& positionOfBindable)
		{
			sf::Vector2f position = sprite.getPosition();
			if (bindPosition(position, keyOfBindable, positionOfBindable)) {
				sprite.setPosition(position);
				return true;
			}
			else return false;
		}
		static bool bindPosition(ngin::UIElement& element,
			const std::string& keyOfBindable,
			const sf::Vector2f& positionOfBindable)
		{
			sf::Vector2f position = element.getPosition();
			if (bindPosition(position, keyOfBindable, positionOfBindable)) {
				element.setPosition(position);
				return true;
			}
			else return false;
		}
	private:
		struct Binder {
			Binder(const sf::Vector2f& lastPosition, const sf::Vector2f& position){
				lastPosition_ = lastPosition;
				position_ = position;
			}
			sf::Vector2f lastPosition_;
			sf::Vector2f position_;
		};

		// holds the initial positions of the objects at the time of binding
		static std::unordered_map<std::string, Binder> bindables;
		static unsigned long int lastLoopCicle_;
	};
}


