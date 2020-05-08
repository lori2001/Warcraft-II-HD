#pragma once
#include "NGin.h"

#include "Map.h"

class Barracks : public sf::Drawable {
public:
	Barracks(const sf::Vector2i& tilePosition) {
		NG_LOG_ERROR(MapFile::getTileSize());
		shape_.setPosition({ Map::getScaledTileSize().x * tilePosition.x, Map::getScaledTileSize().y * tilePosition.y });
		shape_.setSize({ static_cast<float>(textureRect_.width), static_cast<float>(textureRect_.height) });
		shape_.setTexture(&*texture_);
		shape_.setTextureRect(textureRect_);
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(shape_);
	}

private:
	sf::RectangleShape shape_;
	const sf::IntRect textureRect_ = { 5, 5, 122, 116 };

	const ng::TexturePtr texture_ = NG_TEXTURE_SPTR("images/buildings/human_buildings_summer.png");
};