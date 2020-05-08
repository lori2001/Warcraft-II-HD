#include "Minimap.h"

void Minimap::setup(const sf::Vector2f position, const sf::Vector2f size)
{
	// compute distance values to percentage
	const sf::FloatRect viewportDistPer{
		position.x / MAIN_VIEW_WIDTH,
		position.y / MAIN_VIEW_HEIGHT,
		1.0F - (MAIN_VIEW_WIDTH - size.x) / MAIN_VIEW_WIDTH,
		1.0F - (MAIN_VIEW_HEIGHT - size.y) / MAIN_VIEW_HEIGHT,
	};

	// -- Setup View --------------
	minimapView_.reset(sf::FloatRect{ 0, 0, size.x, size.y });
	minimapView_.setViewport(viewportDistPer);

	// always use the bigger parameters to make sure everything fits in container
	sf::Vector2f mapSize = Map::getScaledSize();
	if (mapSize.x >= mapSize.y)
		minimapView_.setSize(ng::ftovec(mapSize.x + Map::getScaledTileSize().x));
	else
		minimapView_.setSize(ng::ftovec(mapSize.y + Map::getScaledTileSize().y));

	minimapView_.setCenter(ng::addVec(Map::getPosition(), ng::divVec(mapSize, ng::ftovec(2.0F))));
	// ----------------------------

	// style of screen mark
	screenMark_.setFillColor({ 0,0,0,0 });
	screenMark_.setOutlineThickness(
		minimapView_.getSize().x / size.x * screenMarkOutlineThickness);
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
