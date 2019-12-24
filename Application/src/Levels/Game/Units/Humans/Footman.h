#pragma once
#include "NGin.h"
#include "../Unit.h"

class Footman : public Unit{
public:
	Footman(sf::Vector2f position) : Unit() {
		texture_ = ngin::Resources::AcquireTexture("images/units/footman.png");

		shape.setTexture(&*texture_);
		shape.setScale({ 2, 2 });
		shape.setSize({ 64, 64 });
		shape.setTextureRect({ 0, 0, 64, 64 });

		int posx = 0, posy = 0;

		for (int y = 0; y < 1080 / 32; y++)
		{
			for (int x = 0; x < 1920 / 32; x++)
			{
				Tiles[x][y].setSize(sf::Vector2f(32, 32));
				Tiles[x][y].setFillColor(sf::Color::Transparent);
				Tiles[x][y].setOutlineColor(sf::Color::Red);
				Tiles[x][y].setOutlineThickness(1.455F);
				Tiles[x][y].setPosition(sf::Vector2f(posx, posy));
				posx += 32;
			}
			posy += 32;
			posx = 0;
		}
	}
	Footman() : Footman({ 0, 0 }) {}

	void setup(const sf::Vector2f& position) { NG_LOG_ERROR("sdw"); }
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void handleEvents(const sf::Event& event, const sf::Vector2f& mouse);
	void animate(const float deltaTime);
	


private:
	
	sf::RectangleShape Tiles[1920/32][1080/32];
	float timer = 0;
	int speed = 9;
	bool shouldMove_ = false;

	sf::Vector2i cursorPosition_;


	std::shared_ptr<sf::Texture> texture_;
	sf::RectangleShape shape;
};