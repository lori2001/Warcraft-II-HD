#include "Cursor.h"

namespace UI
{
	void Cursor::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		states.texture = cursorT;
		target.draw(vertices, states);
	}
	void Cursor::setTexture(sf::Texture & cursorT)
	{
		this->cursorT = &cursorT;
	}
	void Cursor::setPosition(const sf::Vector2f & mouse)
	{
		// define the 4 corners of vertices
		vertices[0].position = sf::Vector2f(mouse.x * 1 / Transformable::getScale().x, mouse.y * 1 / Transformable::getScale().y);
		vertices[1].position = sf::Vector2f(mouse.x * 1 / Transformable::getScale().x + size, mouse.y * 1 / Transformable::getScale().y);
		vertices[2].position = sf::Vector2f(mouse.x * 1 / Transformable::getScale().x + size, mouse.y * 1 / Transformable::getScale().y + size);
		vertices[3].position = sf::Vector2f(mouse.x * 1 / Transformable::getScale().x, mouse.y * 1 / Transformable::getScale().y + size);
	}
}
