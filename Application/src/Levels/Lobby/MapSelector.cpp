#include "MapSelector.h"

MapSelector::MapSelector(const sf::Vector2f& position, const sf::Vector2f& scale)
{
	container_.setTexture(&*texture_);
	mapTitle_.setFillColor({ color::FONT_COLOR_R, color::FONT_COLOR_G, color::FONT_COLOR_B });

	// -- Set Sizes and Scales ---------------
	// leftButton_.setTexturePos({ 0, 0 });
	rightButton_.setTexturePos
	({ static_cast<int>(size::MAP_SELECTOR_BUTTON_WIDTH * 2 + size::MAP_SELECTOR_CONTAINER_WIDTH), 0 });

	container_.setSize({ size::MAP_SELECTOR_CONTAINER_WIDTH, size::MAP_SELECTOR_CONTAINER_HEIGHT });
	container_.setTextureRect({
		static_cast<int>(size::MAP_SELECTOR_BUTTON_WIDTH * 2),
		0,
		static_cast<int>(container_.getSize().x),
		static_cast<int>(container_.getSize().y) });
	// ---------------------------------------

	// --- Set Positions ---------------------
	leftButton_.setPosition(position);

	container_.setPosition({
		leftButton_.getPosition().x + leftButton_.getGlobalBounds().width,
		position.y });

	mapPosition_ = { container_.getPosition().x + 6, container_.getPosition().y + 6 };

	rightButton_.setPosition(
		{ container_.getPosition().x + container_.getGlobalBounds().width,
		position.y });

	ng::centerTextInShape(mapTitle_, container_, -container_.getGlobalBounds().height / 2 - 20);
	// ---------------------------------------

	// --- Load map file ---------------------
	if (!MapFile::scanDir()) {
		// handle error(s)
		std::string error = "Failed to load any maps! Game can not be started!";
		NG_LOG_ERROR(error);
		throw std::runtime_error(error);
	}
	MapFile::load(GameDetailsFile::getMapIndex());
	setupNewMap();
	// ---------------------------------------
}

void MapSelector::handleEvents(const sf::Event& event, const sf::Vector2f& mouse)
{
	leftButton_.handleEvents(event, mouse);
	rightButton_.handleEvents(event, mouse);

	if (leftButton_.isActive()) {
		MapFile::offsetIndexBy(-1);
		GameDetailsFile::setMapIndex(MapFile::getMapIndex());
		setupNewMap();
	}
	else if (rightButton_.isActive()) {
		MapFile::offsetIndexBy(+1);
		GameDetailsFile::setMapIndex(MapFile::getMapIndex());
		setupNewMap();
	}
}

void MapSelector::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(container_);
	target.draw(leftButton_);
	target.draw(rightButton_);
	target.draw(mapTitle_);

	Map::draw(target, states);
}

void MapSelector::setupNewMap()
{
	Map::setup(mapPosition_);

	const sf::Vector2f intendedSize = {
		size::MAP_SELECTOR_CONTAINER_WIDTH - 10,
		size::MAP_SELECTOR_CONTAINER_HEIGHT - 10
	};

	sf::Vector2f mapScale = { intendedSize.x / Map::getLocalBounds().width,
							  intendedSize.y / Map::getLocalBounds().height };

	if (mapScale.x <= mapScale.y) {
		Map::setScale({ mapScale.x, mapScale.x });

		// offset on Y Axis to center
		float yOffset = Map::getLocalBounds().height * mapScale.x;

		Map::setPosition({ mapPosition_.x, mapPosition_.y + intendedSize.y / 2 - yOffset / 2, });

	}
	else {
		Map::setScale({ mapScale.y, mapScale.y });

		// offset on X Axis to center
		float xOffset = Map::getLocalBounds().width * mapScale.y;

		Map::setPosition({ mapPosition_.x + intendedSize.x / 2 - xOffset / 2, mapPosition_.y });
	}

	mapTitle_.setString(MapFile::getMapName());
	ng::centerTextInShape(mapTitle_, container_, -container_.getGlobalBounds().height / 2 - 20);
}

/*
void MapSelector::updateMapTransform()
{
	sf::Vector2i intendedSize = { 330, 286 };

	sf::Vector2f mapScale = { intendedSize.x / map_.getLocalBounds().width,
							  intendedSize.y / map_.getLocalBounds().height };

	if (mapScale.x <= mapScale.y) {
		map_.setScale({ mapScale.x, mapScale.x });

		// offset on Y Axis to center
		float yOffset = map_.getLocalBounds().height * mapScale.x;

		map_.setPosition({ mapPosition_.x, mapPosition_.y + intendedSize.y / 2 - yOffset / 2, });

	}
	else {
		map_.setScale({ mapScale.y, mapScale.y });

		// offset on X Axis to center
		float xOffset = map_.getLocalBounds().width * mapScale.y;

		map_.setPosition({ mapPosition_.x + intendedSize.x / 2 - xOffset / 2, mapPosition_.y });
	}
}
*/

