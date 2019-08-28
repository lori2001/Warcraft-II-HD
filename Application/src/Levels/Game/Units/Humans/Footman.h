#pragma once
#include "NGin.h"

class Footman : public sf::Drawable{
public:
	Footman(sf::Vector2f position);
	Footman() : Footman({ 0, 0 }) {}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	std::shared_ptr<sf::Texture> texture_;
	sf::RectangleShape shape;
};