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
	sf::Vector2f getSize() const;

private:
	std::shared_ptr<sf::Texture> mapTexture_; // singlas resources not to delete map by mistake

	sf::Transformable transformable_;
	sf::VertexArray vertexArray_;
};