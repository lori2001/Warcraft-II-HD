#include "Map.h"

void Map::setup(const sf::Vector2f& position, const sf::Vector2f& scale)
{
	// clear map
	vertexArray_ = sf::VertexArray{};

	mapTexture_ = ng::Resources::AcquireTexture(MapFile::getThemeLocation());

	vertexArray_.setPrimitiveType(sf::Quads);
	vertexArray_.resize(MapFile::getNumOfRows() * MapFile::getMaxNumOfColumns() * 4);

	// size of one tile in texture file
	for (int y = 0; y < MapFile::getNumOfRows(); ++y)
	{
		for (int x = 0; x < MapFile::getNumOfColumns(y); ++x)
		{
			updateBasedOnFile(x, y);
		}
	}

	setPosition(position);
	setScale(scale);
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states)
{
	states.transform = transformable_.getTransform();
	states.texture = &(*mapTexture_);
	target.draw(vertexArray_, states);
}

void Map::setPosition(const sf::Vector2f& position)
{
	transformable_.setPosition(position);
}

void Map::setScale(const sf::Vector2f& scale)
{
	transformable_.setScale(scale);
}

sf::Vector2f Map::getScaledSize()
{
	return { vertexArray_.getBounds().width * transformable_.getScale().x,
			 vertexArray_.getBounds().height * transformable_.getScale().y };
}

void Map::insertTile(const int Xcol, const int Yrow, const int tileIndex)
{
	MapFile::insertTile(Xcol, Yrow, tileIndex);

	if (Yrow < MapFile::getNumOfRows())
	{
		if (Xcol < MapFile::getNumOfColumns(Yrow))
		{
			updateBasedOnFile(Xcol, Yrow);
		}
	}
}

void Map::updateBasedOnFile(const int x, const int y)
{
	const sf::Vector2f tileSize = MapFile::getTileSize();

	// get a pointer to the current tile's quad
	sf::Vertex* quad = &(vertexArray_)[(x + y * MapFile::getMaxNumOfColumns()) * 4];

	// define its 4 corners
	quad[0].position = sf::Vector2f(float(x * tileSize.x), float(y * tileSize.y));
	quad[1].position = sf::Vector2f(float((x + 1) * tileSize.x), float(y * tileSize.y));
	quad[2].position = sf::Vector2f(float((x + 1) * tileSize.x), float((y + 1) * tileSize.y));
	quad[3].position = sf::Vector2f(float(x * tileSize.x), float((y + 1) * tileSize.y));

	int tu = MapFile::getTileNum(x, y) % (mapTexture_->getSize().x / static_cast<int>(tileSize.x));
	int tv = MapFile::getTileNum(x, y) / (mapTexture_->getSize().x / static_cast<int>(tileSize.x));

	quad[0].texCoords = sf::Vector2f(float(tu * (tileSize.x + 1)), float(tv * (tileSize.y + 1)));
	quad[1].texCoords = sf::Vector2f(float(tu * (tileSize.x + 1) + tileSize.x), float(tv * (tileSize.y + 1)));
	quad[2].texCoords = sf::Vector2f(float(tu * (tileSize.x + 1) + tileSize.x), float(tv * (tileSize.y + 1) + tileSize.y));
	quad[3].texCoords = sf::Vector2f(float(tu * (tileSize.x + 1)), float(tv * (tileSize.y + 1) + tileSize.y));
}
