#pragma once
#include "SFML\Graphics.hpp"
#include "..\RW\Settings.h"

namespace UI
{
	class Cursor : public sf::Drawable, public sf::Transformable
	{
	private:
		const unsigned short size = 32;
		sf::Texture *cursorT;

		sf::VertexArray vertices;

	public:
		Cursor()
		{
			vertices.setPrimitiveType(sf::Quads);
			vertices.resize(size * size * 4);

			// define its 4 texture coordinates
			vertices[0].texCoords = sf::Vector2f(0, 0);
			vertices[1].texCoords = sf::Vector2f(size, 0);
			vertices[2].texCoords = sf::Vector2f(size, size);
			vertices[3].texCoords = sf::Vector2f(0, size);
		}
		void setTexture(sf::Texture & cursorT);
		void setPosition(const sf::Vector2f & mouse);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	};
}