#pragma once
#include "NGin.h"
#include "../../Files/MapFile.h"

class Map : private MapFile, public sf::Drawable {
public:

	// needs MapFile's scanDir then load to be called
	enum class MAP_TYPE {
		NORMAL,
		EDITABLE
	};
	static void setup(const sf::Vector2f& position, const MAP_TYPE mapType, const sf::Vector2f& scale = {1, 1});
	static void draw(sf::RenderTarget& target, sf::RenderStates states);

	static void setPosition(const sf::Vector2f& position);
	static void setScale(const sf::Vector2f& scale);

	static sf::FloatRect getLocalBounds() { return vertexArray_.getBounds(); }
	static sf::Vector2f getPosition() { return transformable_.getPosition(); }
	static sf::Vector2f getScaledSize(); // returns 'global bounds' size
	static sf::Vector2f getScale() { return transformable_.getScale(); }
	static sf::Vector2f getOrigin() { return transformable_.getOrigin(); }
	 
	static sf::Vector2f getScaledTileSize() {
		return ng::multiplyVec(MapFile::getTileSize() ,transformable_.getScale());
	}

	// WARNING adds tile to MapFile too
	static void insertTile(int Xcol, int Yrow, const int tileIndex);

private:
	static void updateAllTiles();

	static void setDisplayTile(const int x, const int y, const int tileIndex, const int maxColumns = MapFile::getMaxNumOfColumns());

	static void correctForPositionChanges();
	
	inline static std::shared_ptr<sf::Texture> mapTexture_; // signals resources not to delete map by mistake
	inline static MAP_TYPE currentMapType_;

	inline static sf::Transformable transformable_;
	inline static sf::VertexArray vertexArray_;
	
	inline static sf::Vector2f position_;
	inline static sf::Vector2f insertedTilesNum_; // number of tiles inserted in -1 positions (actually integer)
};
