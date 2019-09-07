#include "Map.h"

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform = transformable_.getTransform();
	states.texture = &(*mapTexture_);
	target.draw(vertexArray_, states);
}

void Map::setMapFile(const MapFile& mapFile)
{
	// clear map
	vertexArray_ = sf::VertexArray{};

	mapTexture_ = ngin::Resources::AcquireTexture(mapFile.getThemeLocation());

	vertexArray_.setPrimitiveType(sf::Quads);
	vertexArray_.resize(mapFile.getNRows() * mapFile.getMaxNColums() * 4);
	int tileSize = mapFile.getTileSize();

	for (int y = 0; y < mapFile.getNRows(); ++y)
	{
		for (int x = 0; x < mapFile.getNColumns(y); ++x)
		{
			// get a pointer to the current tile's quad
			sf::Vertex* quad = &(vertexArray_)[(x + y * mapFile.getMaxNColums()) * 4];

			// define its 4 corners
			quad[0].position = sf::Vector2f(float(x * (tileSize)), float(y * (tileSize)));
			quad[1].position = sf::Vector2f(float((x + 1) * (tileSize)), float(y * (tileSize)));
			quad[2].position = sf::Vector2f(float((x + 1) * (tileSize)), float((y + 1) * (tileSize)));
			quad[3].position = sf::Vector2f(float(x * (tileSize)), float((y + 1) * (tileSize)));

			int tu = mapFile.getTileNum(y, x) % (mapTexture_->getSize().x / (tileSize));
			int tv = mapFile.getTileNum(y, x) / (mapTexture_->getSize().x / (tileSize));

			quad[0].texCoords = sf::Vector2f(float(tu * ((tileSize)+1)), float(tv * ((tileSize)+1)));
			quad[1].texCoords = sf::Vector2f(float((tu) * ((tileSize)+1) + (tileSize)), float(tv * ((tileSize)+1)));
			quad[2].texCoords = sf::Vector2f(float((tu) * ((tileSize)+1) + (tileSize)), float((tv) * ((tileSize)) + (tileSize)));
			quad[3].texCoords = sf::Vector2f(float(tu * ((tileSize)+1)), float((tv) * ((tileSize)+1) + (tileSize)));
		}
	}
}

void Map::setPosition(const sf::Vector2f& position)
{
	transformable_.setPosition(position);
}

void Map::setScale(const sf::Vector2f& scale)
{
	transformable_.setScale(scale);
}

void Map::setSize(const sf::Vector2f& size)
{
	sf::Vector2f mapScale = { size.x / vertexArray_.getBounds().width,
						      size.y / vertexArray_.getBounds().height };

	setScale({ mapScale.x, mapScale.x });
}

sf::Vector2f Map::getSize() const
{
	return { vertexArray_.getBounds().width  * transformable_.getScale().x,
			 vertexArray_.getBounds().height * transformable_.getScale().y };
}