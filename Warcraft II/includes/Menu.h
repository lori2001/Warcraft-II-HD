#pragma once
#include "SFML\Graphics.hpp"

class Menu
{
private:
	sf::RectangleShape menuworks{sf::Vector2f(100,100)};

public:
	bool isActive = true;

	void Setup(sf::RenderWindow &window);
	void handleInput(sf::RenderWindow &window, const sf::Event &event);
	void Update(sf::RenderWindow &window);
	void Compose(sf::RenderWindow &window);
};