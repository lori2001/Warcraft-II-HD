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
		updateMinimap();
	}
}

void MapSelector::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(container_);
	target.draw(leftButton_);
	target.draw(rightButton_);
	target.draw(mapTitle_);

	states.transform = mapTransformable_.getTransform();
	states.texture = &(*mapTexture_);
	target.draw(map_, states);
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
	updateMinimap(); // centering

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

void MapSelector::updateMinimap()
{
	// clear map
	map_ = sf::VertexArray{};

	mapTexture_ = ngin::Resources::AcquireTexture(GameDetails::mapFile.getThemeLocation());

	map_.setPrimitiveType(sf::Quads);
	map_.resize(GameDetails::mapFile.getNRows() * GameDetails::mapFile.getMaxNColums() * 4);
	int tileSize = GameDetails::mapFile.getTileSize();

	for (int y = 0; y < GameDetails::mapFile.getNRows(); ++y)
	{
		for (int x = 0; x < GameDetails::mapFile.getNColumns(y); ++x)
		{
			// get a pointer to the current tile's quad
			sf::Vertex* quad = &(map_)[(x + y * GameDetails::mapFile.getMaxNColums()) * 4];

			// define its 4 corners
			quad[0].position = sf::Vector2f(float(x * (tileSize)), float(y * (tileSize)));
			quad[1].position = sf::Vector2f(float((x + 1) * (tileSize)), float(y * (tileSize)));
			quad[2].position = sf::Vector2f(float((x + 1) * (tileSize)), float((y + 1) * (tileSize)));
			quad[3].position = sf::Vector2f(float(x * (tileSize)), float((y + 1) * (tileSize)));

			int tu = GameDetails::mapFile.getTileNum(y, x) % (mapTexture_->getSize().x / (tileSize));
			int tv = GameDetails::mapFile.getTileNum(y, x) / (mapTexture_->getSize().x / (tileSize));

			quad[0].texCoords = sf::Vector2f(float(tu * ((tileSize)+1)), float(tv * ((tileSize)+1)));
			quad[1].texCoords = sf::Vector2f(float((tu) * ((tileSize)+1) + (tileSize)), float(tv * ((tileSize)+1)));
			quad[2].texCoords = sf::Vector2f(float((tu) * ((tileSize)+1) + (tileSize)), float((tv) * ((tileSize)) + (tileSize)));
			quad[3].texCoords = sf::Vector2f(float(tu * ((tileSize)+1)), float((tv) * ((tileSize)+1) + (tileSize)));
		}
	}

	sf::Vector2i intendedSize = { 330, 286 };

	sf::Vector2f mapScale = { intendedSize.x / map_.getBounds().width,
							  intendedSize.y / map_.getBounds().height };

	if (mapScale.x <= mapScale.y) {
		mapTransformable_.setScale({ mapScale.x, mapScale.x });

		sf::Vector2f actualSize = { map_.getBounds().width  * mapScale.x,
									map_.getBounds().height * mapScale.x };

		mapTransformable_.setPosition(
			{ mapPosition_.x, mapPosition_.y + intendedSize.y / 2 - actualSize.y / 2, }
		);

	}
	else {
		mapTransformable_.setScale({ mapScale.y, mapScale.y });

		sf::Vector2f actualSize = { map_.getBounds().width  * mapScale.y,
									map_.getBounds().height * mapScale.y };

		mapTransformable_.setPosition(
			{ mapPosition_.x + intendedSize.x / 2 - actualSize.x / 2, mapPosition_.y }
		);
	}
}
