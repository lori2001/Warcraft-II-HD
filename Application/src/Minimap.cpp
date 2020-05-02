#include "Minimap.h"

void Minimap::setup()
{
	minimapView_.setViewport(viewportPercent_);

	// always use the bigger parameters to make sure everything fits in container
	sf::Vector2f mapSize = Map::getScaledSize();
	if (mapSize.x >= mapSize.y)
		minimapView_.setSize(ng::ftovec(mapSize.x));
	else
		minimapView_.setSize(ng::ftovec(mapSize.y));

	minimapView_.setCenter(ng::divVec(mapSize, ng::ftovec(2.0F)));

	// style of screen mark
	screenMark_.setFillColor({0,0,0,0});
	screenMark_.setOutlineThickness(
		minimapView_.getSize().x / viewSize_.x * screenMarkOutlineThickness);
	screenMark_.setOutlineColor(screenMarkColor_);
}

void Minimap::handleEvents(const sf::Event& event)
{
}

void Minimap::update()
{
}

void Minimap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	ng::Main::setWindowView(minimapView_);

	Map::draw(target, states);
	target.draw(screenMark_);

	ng::Main::applyDefaultViewToWindow();
}

void Minimap::adjustScreenMark(const sf::Vector2f& viewSize, const sf::Vector2f& viewCenterPos)
{
	// percentage of viewSize compared to map's scaled size, scaled to minimap's size
	screenMark_.setSize(viewSize);
	
	// set origin to center
	screenMark_.setOrigin(ng::divVec(screenMark_.getSize(), ng::ftovec(2.0F)));
	
	// scale position accordingly
	screenMark_.setPosition(viewCenterPos);
}
