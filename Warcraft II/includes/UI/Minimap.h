#pragma once
#include "SFML\Graphics.hpp"
#include "..\RW\Loading.h"
#include "..\RW\Settings.h"
#include "..\RW\MapReader.h"

namespace UI
{
	class Minimap : public sf::Drawable, public sf::Transformable
	{
	private:
		const short *tilesize = new const short{ 32 }; //size of 1 tile
		const sf::Vector2f *minimapsize = new const sf::Vector2f{ 328,284 }; //size of the minimap (exactly fits the in-game UI)
		sf::Vector2i *tilessize = new sf::Vector2i{ 0, 0 }; //number of tiles x and y

		sf::VertexArray *tilesV = new sf::VertexArray;
		sf::Texture *tilesT = new sf::Texture; // the texture used by the map
		sf::Texture *summertilesT = new sf::Texture;
		sf::Texture *wastelandtilesT = new sf::Texture;
		sf::Texture *wintertilesT = new sf::Texture;

		sf::Vector2f *scale = new sf::Vector2f; // holds the last scale inputed in set scale

		float round(float &x);
	public:
		~Minimap()
		{
			delete tilesize;
			delete minimapsize;
			delete tilessize;
			delete tilesV;
			delete tilesT;
			delete summertilesT;
			delete wastelandtilesT;
			delete wintertilesT;
		}
		//used to move minimap with view and interface (in case of in-game minimap only)
		void move(float x, float y);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		//setters
		void setTexture(const sf::Texture &summertilesT, const sf::Texture &wastelandtilesT, const sf::Texture &wintertilesT);
		void setTiles(const RW::MapReader &mapreader);
		void setScale(const sf::Vector2f &scale);

		//getters
		//returns the size of the currently displayed minimap
		sf::Vector2f getContainerSize() { return sf::Vector2f(minimapsize->x * scale->x, minimapsize->y * scale->y); }
		//returns the size of the currently displayed map right now on screen
		sf::Vector2f getScaledSize()
		{
			if (tilessize->x > tilessize->y)
				return sf::Vector2f(tilessize->x * (*tilesize) * ((minimapsize->x * scale->x) / (tilessize->x * (*tilesize))), tilessize->y * (*tilesize) * ((minimapsize->x * scale->x) / (tilessize->x * (*tilesize))));
			else
				return sf::Vector2f(tilessize->x * (*tilesize) * ((minimapsize->y * scale->y) / (tilessize->y * (*tilesize))), tilessize->y * (*tilesize) * ((minimapsize->y * scale->y) / (tilessize->y * (*tilesize))));
		}
	};
}