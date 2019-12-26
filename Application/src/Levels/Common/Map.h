#pragma once
#include "NGin.h"
#include "../../Files/MapFile.h"

class Map : public sf::Drawable {
public:

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void setMapFile(const MapFile& mapFile);
	
	void setPosition(const sf::Vector2f& position);
	void setScale(const sf::Vector2f& scale);
	// uses setScale()
	void setSize(const sf::Vector2f& size);

	sf::FloatRect getLocalBounds() const { return vertexArray_.getBounds(); }
	sf::Vector2f getPosition() const { return transformable_.getPosition(); }
	sf::Vector2f getSize() const; // returns 'global bounds' size
	sf::Vector2f getScale() const { return transformable_.getScale(); }

protected:
	sf::Vector2f getTileSize() { return tileSize_; } // defaults to none
	
private:
	std::shared_ptr<sf::Texture> mapTexture_; // singlas resources not to delete map by mistake

	sf::Vector2f tileSize_ = { 0, 0 }; // defaults to none

	sf::Transformable transformable_;
	sf::VertexArray vertexArray_;
};