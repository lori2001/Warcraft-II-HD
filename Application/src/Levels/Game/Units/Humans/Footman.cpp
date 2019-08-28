#include "Footman.h"

Footman::Footman(sf::Vector2f position)
{
	texture_ = ngin::Resources::AcquireTexture("images/units/footman.png");
	
	shape.setTexture(&*texture_);
	shape.setScale({2, 2});
	shape.setSize({64, 64});
	shape.setTextureRect({0, 0, 64, 64});
}

void Footman::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape);
}
