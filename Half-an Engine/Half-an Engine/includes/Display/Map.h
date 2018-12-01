#pragma once
#include <math.h>
#include "SFML\Graphics.hpp"
#include "..\RW\MapReader.h"

namespace Display
{
	class Map : public sf::Drawable, public sf::Transformable
	{
	private:
		const int tilesize = 32; //size of 1 tile
		sf::Vector2i tilessize{ 0, 0 }; //number of tiles x and y
		const sf::Vector2f mapsize{ 1920,1040 }; //size of the map (unscaled) 

		sf::VertexArray tilesV;
		sf::Texture tilesT; // the texture used by the map
		sf::Texture summertilesT;
		sf::Texture wastelandtilesT;
		sf::Texture wintertilesT;

		float usedScale; // holds used scale
	public:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		//setters
		void setTexture(const sf::Texture &summertilesT, const sf::Texture &wastelandtilesT, const sf::Texture &wintertilesT);
		void setTiles(const RW::MapReader &mapreader);
		void setScale(const sf::Vector2f &scale);
		void setPosition(sf::Vector2f position);

		//getters
		//returns the size of the currently displayed map right now on screen
		sf::Vector2f getScaledSize() const { return sf::Vector2f(getSize().x * Transformable::getScale().x, getSize().y * Transformable::getScale().y); }
		sf::Vector2f getSize() const { return sf::Vector2f(float(tilessize.x * tilesize), float(tilessize.y * tilesize)); }
		float getScale() const { return usedScale; }
	};
}
