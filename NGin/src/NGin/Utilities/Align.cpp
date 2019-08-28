#include "Align.h"

namespace ngin {
	void positionTextInBounds(sf::Vector2f position, sf::Text& text, const sf::FloatRect& bounds)
	{
		// skip empty text avoiding errors
		text.setPosition({ bounds.left + position.x, bounds.top + position.y - (text.getLocalBounds().top) });
	}
	void positionTextInShape(sf::Vector2f position, sf::Text& text, const sf::RectangleShape& shape)
	{
		// corrects for outline misposition
		if (shape.getOutlineThickness() > 0) {
			positionTextInBounds(position, text, {
			shape.getGlobalBounds().left,
			shape.getGlobalBounds().top,
			shape.getGlobalBounds().width - shape.getOutlineThickness() ,
			shape.getGlobalBounds().height - shape.getOutlineThickness() });
		}
		else positionTextInBounds(position, text, shape.getGlobalBounds());
	}
	void centerTextInBounds(sf::Text& text, const sf::FloatRect& bounds)
	{
		if (text.getString() == "" || text.getFont() == 0) return;

		const sf::Vector2f position = { 
			(bounds.width  / 2) - (text.getGlobalBounds().width  / 2),
			(bounds.height / 2) - (text.getGlobalBounds().height / 2) };

		positionTextInBounds(position, text, bounds);
	}
	void centerTextInShape(sf::Text& text, const sf::RectangleShape& shape)
	{
		if (text.getString() == "" || text.getFont() == 0) return;

		centerTextInBounds(text, shape.getGlobalBounds());
	}
	void centerTextInBounds(float xOffset, sf::Text& text, const sf::FloatRect& bounds)
	{
		if (text.getString() == "" || text.getFont() == 0) return;

		const sf::Vector2f position = {
			(bounds.width / 2) - (text.getGlobalBounds().width / 2) + xOffset,
			(bounds.height / 2) - (text.getGlobalBounds().height / 2)};

		positionTextInBounds(position, text, bounds);
	}
	void centerTextInShape(float xOffset, sf::Text& text, const sf::RectangleShape& shape)
	{
		if (text.getString() == "" || text.getFont() == 0) return;

		centerTextInBounds( xOffset, text, shape.getGlobalBounds());
	}
	void centerTextInBounds(sf::Text& text, const sf::FloatRect& bounds, float yOffset)
	{
		if (text.getString() == "" || text.getFont() == 0 ) return;

		const sf::Vector2f position = {
			(bounds.width / 2) - (text.getGlobalBounds().width / 2),
			(bounds.height / 2) - (text.getGlobalBounds().height / 2) + yOffset};

		positionTextInBounds( position, text, bounds);
	}
	void centerTextInShape(sf::Text& text, const sf::RectangleShape& shape, float yOffset)
	{
		if (text.getString() == "" || text.getFont() == 0) return;

		centerTextInBounds(text, shape.getGlobalBounds(), yOffset);
	}
}
