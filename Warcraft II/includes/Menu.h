#pragma once
#include "SFML\Graphics.hpp"
#include "RW/Loading.h"
#include "UI/Button.h"

class Menu
{
private:
	sf::Vector2f mouse; //holds position of the mouse

	UI::Button menuworks{ "Works!", sf::Vector2f(224,28) };

	RW::Loading loading;

public:
	bool isActive = true;

	void Setup(sf::RenderWindow &window);
	void handleInput(sf::RenderWindow &window, const sf::Event &event);
	void Update(sf::RenderWindow &window);
	void Compose(sf::RenderWindow &window);
};