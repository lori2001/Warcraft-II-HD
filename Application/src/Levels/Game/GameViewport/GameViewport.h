#pragma once
#include "NGin.h"

#include "../../../Style.h"

class GameViewport : public ng::Level {
public:
	GameViewport();

	void handleEvents(const sf::Event& event);
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	~GameViewport();
private:

	sf::RectangleShape test;
};