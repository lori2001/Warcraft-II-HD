#include "Map.h"

namespace Display 
{
	void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// apply the transform
		states.transform *= getTransform();

		// apply the tileset texture
		states.texture = &(tilesT);

		// draw the vertex array
		target.draw(tilesV, states);
	}
	void Map::setTexture(const sf::Texture & summertilesT, const sf::Texture & wastelandtilesT, const sf::Texture & wintertilesT)
	{
		this->summertilesT = summertilesT;
		this->wastelandtilesT = wastelandtilesT;
		this->wintertilesT = wintertilesT;
	}
	void Map::setTiles(const RW::MapReader &mapreader)
	{
		tilessize = mapreader.getTilessize();

		if (mapreader.getTheme() == 0)
			tilesT = summertilesT;
		else if (mapreader.getTheme() == 1)
			tilesT = wastelandtilesT;
		else if (mapreader.getTheme() == 2)
			tilesT = wintertilesT;

		tilesV.setPrimitiveType(sf::Quads);
		tilesV.resize(tilessize.x * tilessize.y * 4);

		for (int y = 0; y < tilessize.y; ++y)
		{
			for (int x = 0; x < tilessize.x; ++x)
			{
				// get a pointer to the current tile's quad
				sf::Vertex* quad = &(tilesV)[(x + y * tilessize.x) * 4];

				// define its 4 corners
				quad[0].position = sf::Vector2f(float(x * (tilesize)), float(y * (tilesize)));
				quad[1].position = sf::Vector2f(float((x + 1) * (tilesize)), float(y * (tilesize)));
				quad[2].position = sf::Vector2f(float((x + 1) * (tilesize)), float((y + 1) * (tilesize)));
				quad[3].position = sf::Vector2f(float(x * (tilesize)), float((y + 1) * (tilesize)));

				int tu = mapreader.getTiles(x, y) % (tilesT.getSize().x / (tilesize));
				int tv = mapreader.getTiles(x, y) / (tilesT.getSize().x / (tilesize));

				quad[0].texCoords = sf::Vector2f(float(tu * ((tilesize)+1)), float(tv * ((tilesize)+1)));
				quad[1].texCoords = sf::Vector2f(float((tu) * ((tilesize)+1) + (tilesize)), float(tv * ((tilesize)+1)));
				quad[2].texCoords = sf::Vector2f(float((tu) * ((tilesize)+1) + (tilesize)), float((tv) * ((tilesize)) + (tilesize)));
				quad[3].texCoords = sf::Vector2f(float(tu * ((tilesize)+1)), float((tv) * ((tilesize)+1) + (tilesize)));
			}
		}
	}
	void Map::setScale(const sf::Vector2f &scale)
	{
		usedScale = 0;

		//scales according to the bigger size
		if ((mapsize.y * scale.y) / (tilessize.y * (tilesize)) < (mapsize.x * scale.x) / (tilessize.x * (tilesize)))
			usedScale = (mapsize.y * scale.y) / (tilessize.y * (tilesize));
		else
			usedScale = (mapsize.x * scale.x) / (tilessize.y * (tilesize));

		Transformable::setScale(usedScale, usedScale);
	}
	void Map::setPosition(sf::Vector2f position)
	{
		position.x = round(position.x);
		position.y = round(position.y);

		Transformable::setPosition(position);
	}
}