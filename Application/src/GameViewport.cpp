#include "GameViewport.h"

GameViewport::GameViewport()
{
	Map::setup({ 0, 0 }, Map::MAP_TYPE::NORMAL, mapScale_);

	gameView_.setViewport(viewportPercent_);
}

void GameViewport::handleEvents(const sf::Event& event)
{
}

void GameViewport::update()
{
}

void GameViewport::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	ng::Main::setWindowView(gameView_);
	Map::draw(target, states);

	ng::Main::applyDefaultViewToWindow();
}

GameViewport::~GameViewport()
{
}
