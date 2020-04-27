#pragma once
#include "NGin.h"
#include "../../Files/MapFile.h"

class Map : private MapFile, public sf::Drawable {
public:

	// needs MapFile's scanDir then load to be called
	static void setup(const sf::Vector2f& position, const sf::Vector2f& scale = {1, 1});
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
	static void insertTile(const int Xcol, const int Yrow, const int tileIndex);

private:
	static void updateBasedOnFile(const int x, const int y);

	inline static std::shared_ptr<sf::Texture> mapTexture_; // singlas resources not to delete map by mistake

	inline static sf::Transformable transformable_;
	inline static sf::VertexArray vertexArray_;
};
