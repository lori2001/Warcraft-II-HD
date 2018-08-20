#include "Minimap.h"

namespace UI
{
	float Minimap::round(float &x)
	{
		float whole;
		if (std::modf(x, &whole) >= 0.5f)
			return x >= 0 ? ceil(x) : floor(x);
		else
			return x < 0 ? ceil(x) : floor(x);
	}
	void Minimap::move(float x, float y)
	{
		Transformable::setPosition(Transformable::getPosition().x + x, Transformable::getPosition().y + y);
	}
	void Minimap::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// apply the transform
		states.transform *= getTransform();

		// apply the tileset texture
		states.texture = &(*tilesT);

		// draw the vertex array
		target.draw(*tilesV, states);
	}
	void Minimap::setTexture(const sf::Texture & summertilesT, const sf::Texture & wastelandtilesT, const sf::Texture & wintertilesT)
	{
		*this->summertilesT = summertilesT;
		*this->wastelandtilesT = wastelandtilesT;
		*this->wintertilesT = wintertilesT;
	}
	void Minimap::setTiles(const RW::MapReader &mapreader)
	{ 
		*tilessize = mapreader.getTilessize();

		if (mapreader.getTheme() == 0)
			*tilesT = *summertilesT;
		else if (mapreader.getTheme() == 1)
			*tilesT = *wastelandtilesT;
		else if (mapreader.getTheme() == 2)
			*tilesT = *wintertilesT;

		tilesV->setPrimitiveType(sf::Quads);
		tilesV->resize(tilessize->x * tilessize->y * 4);
		
		for (int y = 0; y < tilessize->y; ++y)
			for (int x = 0; x < tilessize->x; ++x)
			{
				// get a pointer to the current tile's quad
				sf::Vertex* quad = &(*tilesV)[(x + y * tilessize->x) * 4];

				// define its 4 corners
				quad[0].position = sf::Vector2f(float(x * (*tilesize)), float(y * (*tilesize)));
				quad[1].position = sf::Vector2f(float((x + 1) * (*tilesize)), float(y * (*tilesize)));
				quad[2].position = sf::Vector2f(float((x + 1) * (*tilesize)), float((y + 1) * (*tilesize)));
				quad[3].position = sf::Vector2f(float(x * (*tilesize)), float((y + 1) * (*tilesize)));

				int tu = mapreader.getTiles(x, y) % (tilesT->getSize().x / (*tilesize));
				int tv = mapreader.getTiles(x, y) / (tilesT->getSize().x / (*tilesize));

				quad[0].texCoords = sf::Vector2f(float(tu * ((*tilesize) + 1)), float(tv * ((*tilesize) + 1)));
				quad[1].texCoords = sf::Vector2f(float((tu) * ((*tilesize) + 1) + (*tilesize)), float(tv * ((*tilesize) + 1)));
				quad[2].texCoords = sf::Vector2f(float((tu) * ((*tilesize) + 1) + (*tilesize)), float((tv) * ((*tilesize)) + (*tilesize)));
				quad[3].texCoords = sf::Vector2f(float(tu * ((*tilesize) + 1)), float((tv) * ((*tilesize) + 1) + (*tilesize)));
			}
	}
	void Minimap::setScale(const sf::Vector2f &scale)
	{
		//saves scale for further use
		*this->scale = scale;

		float usedScale;

		//scales according to the bigger size
		if (tilessize->x > tilessize->y)
			usedScale = (minimapsize->x * scale.x) / (tilessize->x * (*tilesize));
		else
			usedScale = (minimapsize->y * scale.y) / (tilessize->y * (*tilesize));

		float temp; // holds the part that needs to be cut
		float whole; // not really used (just for modf to work

		temp = usedScale * 10000; // separates the last two digits by the decimal (y.xxxxxx)=>(yyyyy.xx)
		temp = std::modf(temp, &whole); // gets rid of whole part
		temp /= 10000; //puts the las to decimals back to their original position

		usedScale -= temp;

		Transformable::setScale(usedScale, usedScale);
	}
}