#pragma once
#include "NGin.h"

class Unit : public sf::Drawable
{
public:
	virtual void setup(const sf::Vector2f& position) = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	virtual void handleEvents(const sf::Event& event, const sf::Vector2f& mouse) = 0;
	virtual void animate(const float deltaTime) = 0;

protected:
	Unit();

	void findPathTo(const sf::Vector2i& position);

	sf::Vector2i position_;
	sf::Vector2i test;
	std::vector <sf::Vector2i> tests;
	
private:

	ngin::AStar::Generator generator;
};