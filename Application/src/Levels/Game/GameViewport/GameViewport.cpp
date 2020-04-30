#include "GameViewport.h"

GameViewport::GameViewport()
{
	test.setFillColor(sf::Color::Red);
	test.setSize({ 200, 200 });
}

void GameViewport::handleEvents(const sf::Event& event)
{
}

void GameViewport::update()
{
}

void GameViewport::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(test);
}

GameViewport::~GameViewport()
{
}
