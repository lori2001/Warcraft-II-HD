#pragma once
#include "SFML\Graphics.hpp"

namespace UI
{
	class Cursor : public sf::Drawable, public sf::Transformable
	{
	private:
		const int size = 64;
		sf::Texture cursorT;

		sf::VertexArray vertices;
	public:
		Cursor()
		{
			vertices.setPrimitiveType(sf::Quads);
			vertices.resize(size * size * 4);

			// define its 4 texture coordinates
			vertices[0].texCoords = sf::Vector2f(0, 0);
			vertices[1].texCoords = sf::Vector2f((float)size, 0);
			vertices[2].texCoords = sf::Vector2f((float)size, (float)size);
			vertices[3].texCoords = sf::Vector2f(0, (float)size);

			//scales the cursor down a bit
			Transformable::setScale({ 0.85f, 0.85f });
		}
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		void setTexture(sf::Texture & cursorT);
		void setPosition(const sf::Vector2f & mouse);
	};
}