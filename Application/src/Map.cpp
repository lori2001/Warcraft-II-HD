#include "Map.h"

void Map::setup(const sf::Vector2f& position, const MAP_TYPE mapType, const sf::Vector2f& scale)
{
	mapTexture_ = ng::Resources::AcquireTexture(MapFile::getThemeLocation());
	currentMapType_ = mapType;

	insertedTilesNum_ = { 0,0 }; // reset
	updateAllTiles();

	setScale(scale);
	setPosition(position);
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states)
{
	states.transform = transformable_.getTransform();
	states.texture = &(*mapTexture_);
	target.draw(vertexArray_, states);
}

void Map::setPosition(const sf::Vector2f& position)
{
	position_ = position;
	correctForPositionChanges();
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

void Map::insertTile(int Xcol, int Yrow, const int tileIndex)
{
	Yrow += insertedTilesNum_.y;
	Xcol += insertedTilesNum_.x;

	const MapFile::INSERT_RET returnVal = MapFile::insertTile(Xcol, Yrow, tileIndex);
	if (returnVal == MapFile::INSERT_RET::X_NEGATIVE_Y_NEGATIVE)
	{
		insertedTilesNum_.x++;
		insertedTilesNum_.y++;
		updateAllTiles();
	}
	else if (returnVal == MapFile::INSERT_RET::X_TOO_BIG_Y_NEGATIVE ||
			 returnVal == MapFile::INSERT_RET::X_OK_Y_NEGATIVE)
	{
		insertedTilesNum_.y++;
		updateAllTiles();
	}
	else if (returnVal == MapFile::INSERT_RET::X_NEGATIVE_Y_OK ||
		     returnVal == MapFile::INSERT_RET::X_NEGATIVE_Y_TOO_BIG)
	{
		insertedTilesNum_.x++;
		updateAllTiles();
	}
	else if (returnVal == MapFile::INSERT_RET::X_TOO_BIG_Y_OK ||
			 returnVal == MapFile::INSERT_RET::X_OK_Y_TOO_BIG ||
			 returnVal == MapFile::INSERT_RET::X_TOO_BIG_Y_TOO_BIG)
	{
		updateAllTiles();
	}
	else if (returnVal == MapFile::INSERT_RET::ALL_OK)
	{
		if (currentMapType_ == MAP_TYPE::EDITABLE) {
			Xcol++; Yrow++;
		}
		
		if (currentMapType_ == MAP_TYPE::EDITABLE) {
			setDisplayTile(Xcol, Yrow, tileIndex, MapFile::getMaxNumOfColumns() + 2);
		}
		else if (currentMapType_ == MAP_TYPE::NORMAL) {
			setDisplayTile(Xcol, Yrow, tileIndex);
		}
	}
}

void Map::correctForPositionChanges()
{
	sf::Vector2f shiftByTilesNum{ static_cast<float>(insertedTilesNum_.x), static_cast<float>(insertedTilesNum_.y) };
	if (currentMapType_ == MAP_TYPE::EDITABLE) {
		shiftByTilesNum.x+=1;
		shiftByTilesNum.y+=1;
	}
	transformable_.setPosition(ng::subsVec(position_, ng::multiplyVec(shiftByTilesNum, getScaledTileSize())) );
}

void Map::updateAllTiles()
{
	vertexArray_ = sf::VertexArray{}; // clear map
	vertexArray_.setPrimitiveType(sf::Quads);

	correctForPositionChanges();

	if (currentMapType_ == MAP_TYPE::NORMAL) {
		vertexArray_.resize(MapFile::getNumOfRows() * MapFile::getMaxNumOfColumns() * 4);
		for (int y = 0; y < MapFile::getNumOfRows(); ++y)
		{
			for (int x = 0; x < MapFile::getNumOfColumns(y); ++x)
			{
				setDisplayTile(x, y, MapFile::getTileNum(x, y));
			}
		}
	}
	else if (currentMapType_ == MAP_TYPE::EDITABLE)
	{
		const int maxNumOfCols = MapFile::getMaxNumOfColumns() + 2;
		vertexArray_.resize((MapFile::getNumOfRows() + 2) * maxNumOfCols * 4);

		for (int x = 0; x < MapFile::getNumOfColumns(0) + 2; ++x)
		{
			setDisplayTile(x, 0, MapFile::placeholderTileNum_, maxNumOfCols);
		}
		for (int y = 1; y <= MapFile::getNumOfRows(); ++y)
		{
			setDisplayTile(0, y, MapFile::placeholderTileNum_, maxNumOfCols);
			for (int x = 1; x <= MapFile::getNumOfColumns(y - 1); ++x)
			{
				setDisplayTile(x, y, MapFile::getTileNum(x - 1, y - 1), maxNumOfCols);
			}
			setDisplayTile(MapFile::getNumOfColumns(y - 1) + 1, y, MapFile::placeholderTileNum_, maxNumOfCols);
		}
		for (int x = 0; x < MapFile::getNumOfColumns(MapFile::getNumOfRows()-1) + 2; ++x)
		{
			setDisplayTile(x, MapFile::getNumOfRows() + 1, MapFile::placeholderTileNum_, maxNumOfCols);
		}
	}
}

void Map::setDisplayTile(const int x, const int y, const int tileIndex, const int maxColumns)
{
	// size of one tile in texture file
	const sf::Vector2f tileSize = MapFile::getTileSize();

	// get a pointer to the current tile's quad
	sf::Vertex* quad = &(vertexArray_)[(x + y * maxColumns) * 4];

	// define its 4 corners
	quad[0].position = sf::Vector2f(float(x * tileSize.x), float(y * tileSize.y));
	quad[1].position = sf::Vector2f(float((x + 1) * tileSize.x), float(y * tileSize.y));
	quad[2].position = sf::Vector2f(float((x + 1) * tileSize.x), float((y + 1) * tileSize.y));
	quad[3].position = sf::Vector2f(float(x * tileSize.x), float((y + 1) * tileSize.y));

	int tu = tileIndex % (mapTexture_->getSize().x / static_cast<int>(tileSize.x));
	int tv = tileIndex / (mapTexture_->getSize().x / static_cast<int>(tileSize.x));

	quad[0].texCoords = sf::Vector2f(float(tu * (tileSize.x + 1)), float(tv * (tileSize.y + 1)));
	quad[1].texCoords = sf::Vector2f(float(tu * (tileSize.x + 1) + tileSize.x), float(tv * (tileSize.y + 1)));
	quad[2].texCoords = sf::Vector2f(float(tu * (tileSize.x + 1) + tileSize.x), float(tv * (tileSize.y + 1) + tileSize.y));
	quad[3].texCoords = sf::Vector2f(float(tu * (tileSize.x + 1)), float(tv * (tileSize.y + 1) + tileSize.y));
}
