#pragma once
#include "SFML/Graphics.hpp"

namespace ngin {
	void positionTextInBounds(sf::Vector2f position, sf::Text& text, const sf::FloatRect& bounds);
	void positionTextInShape(sf::Vector2f position, sf::Text& text, const sf::RectangleShape& shape);

	void centerTextInBounds(sf::Text& text, const sf::FloatRect& bounds);
	void centerTextInShape(sf::Text& text, const sf::RectangleShape& shape);

	void centerTextInBounds(float xOffset, sf::Text& text, const sf::FloatRect& bounds);
	void centerTextInShape(float xOffset, sf::Text& text, const sf::RectangleShape& shape);

	void centerTextInBounds(sf::Text& text, const sf::FloatRect& bounds, float yOffset);
	void centerTextInShape(sf::Text& text, const sf::RectangleShape& shape, float yOffset);
}

