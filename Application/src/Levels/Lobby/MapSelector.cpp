#include "MapSelector.h"

void MapSelector::handleEvents(const sf::Event& event, const sf::Vector2f& mouse)
{
	leftButton_.handleEvents(event, mouse);
	rightButton_.handleEvents(event, mouse);

	if (leftButton_.isActive()) {
		GameDetails::mapFile.offsetIndexBy(-1);
	}
	else if (rightButton_.isActive()) {
		GameDetails::mapFile.offsetIndexBy(+1);
	}

	if (leftButton_.isActive() || rightButton_.isActive()) {
		setTitle(GameDetails::mapFile.getMapName());
		map_.setMapFile(GameDetails::mapFile);
		updateMapTransform();
	}
}

void MapSelector::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(container_);
	target.draw(leftButton_);
	target.draw(rightButton_);
	target.draw(mapTitle_);
	target.draw(map_);
}

void MapSelector::setTexture(const sf::Texture& texture)
{
	container_.setTexture(&texture);
	leftButton_.setTexture(texture);
	rightButton_.setTexture(texture);
}

void MapSelector::setPosition(const sf::Vector2f& position)
{
	leftButton_.setPosition(position);

	container_.setPosition({
		leftButton_.getPosition().x + leftButton_.getGlobalBounds().width,
		position.y});


	mapPosition_ = { container_.getPosition().x + 6, container_.getPosition().y + 6 };
	map_.setPosition(mapPosition_);
	updateMapTransform();

	rightButton_.setPosition(
		{ container_.getPosition().x + container_.getGlobalBounds().width,
		position.y });

	ngin::centerTextInShape(mapTitle_, container_, - container_.getGlobalBounds().height / 2 - 20);
}

void MapSelector::setSize(const sf::Vector2f& buttonSize, const sf::Vector2f& containerSize)
{
	leftButton_.setSize(buttonSize); // 39 297
	leftButton_.setTexturePos({ 0, 0});
	rightButton_.setSize(buttonSize);
	rightButton_.setTexturePos({ 418, 0 });

	container_.setSize(containerSize);

	container_.setTextureRect({
		78,
		0,
		static_cast<int>(containerSize.x),
		static_cast<int>(containerSize.y) }); // 340 297
}

void MapSelector::setTitle(const std::string& titleString)
{
	mapTitle_.setString(titleString);

	ngin::centerTextInShape(mapTitle_, container_, -container_.getGlobalBounds().height / 2 - 20);
}

void MapSelector::setSelectColor(const sf::Color& color)
{
	leftButton_.setSelectColor(color);
	rightButton_.setSelectColor(color);
}

void MapSelector::setSelectThickness(const float thickness)
{
	leftButton_.setSelectThickness(thickness);
	rightButton_.setSelectThickness(thickness);
}

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
