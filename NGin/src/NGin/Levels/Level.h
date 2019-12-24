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

		int getResponse() { return response_; }

	protected:
		int response_ = -1;
	};
}
