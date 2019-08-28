#pragma once
#include "SFML/Graphics.hpp"
#include "MainLevel.h"

namespace ngin {
	class Level : public sf::Drawable
	{
	public:
		virtual ~Level() = default;

		// gets called once in the beginning
		virtual void setup() = 0;
		// gets called only if there is an ongoing event
		virtual void handleEvents(const sf::Event& event) = 0;
		// gets called every frame but is not constant
		virtual void update() = 0;
		// gets called every frame but should only draw on window
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

		// can be called to change window settings
		virtual void changeWindow(sf::VideoMode& windowVideoMode,
								  sf::String& windowName,
								  ngin::MainLevel::WINDOW_TYPE& windowType) {}

		// can be called to get window settings without changing them
		virtual void getFromWindow(const sf::VideoMode& windowVideoMode,
								   const sf::String& windowName,
								   const ngin::MainLevel::WINDOW_TYPE& windowType) {}

		int getResponse() { return response_; }

	protected:
		int response_ = -1;
	};
}
