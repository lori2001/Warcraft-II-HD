#include "Gears.h"

void Gears::setTopPosition(const sf::Vector2f & position)
{
	topgearsS->setPosition(position);
}

void Gears::setBotPosition(const sf::Vector2f & position)
{
	botgearsS->setPosition(position);
}

void Gears::setTopScale(const sf::Vector2f & scale)
{
	topgearsS->setScale(scale);
}

void Gears::setBotScale(const sf::Vector2f & scale)
{
	botgearsS->setScale(scale);
}

void Gears::animate()
{
	if (clock->getElapsedTime().asSeconds() > *SPF)
	{
		(*curr)++;
		clock->restart();
		if (*curr >= *SIZE)
			*curr = 0;

		topgearsS->setTexture(loading.topgearsT[*curr]);
		botgearsS->setTexture(loading.botgearsT[*curr]);
	}
}

void Gears::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(*topgearsS, states);
	target.draw(*botgearsS, states);
}
