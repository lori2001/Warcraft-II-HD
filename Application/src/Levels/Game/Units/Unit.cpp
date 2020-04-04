#include "Unit.h"

Unit::Unit() {
	generator.setWorldSize({ 1920/32, 1080/32 });
	generator.setHeuristic(ng::AStar::Heuristic::euclidean);
	generator.setDiagonalMovement(true);

	position_ = { 0, 0 };
}

void Unit::findPathTo(const sf::Vector2i& cursorPosition)
{
	auto path = generator.findPath({ position_.x, position_.y }, { cursorPosition.x ,cursorPosition.y });
	
	for (auto& coordinate : path)
	{
		//NG_LOG_ERROR("In Unit:", "i = ", i++, "location :", test.x, " ", test.y);
	    //NG_LOG_ERROR("size : ", tests.size());
		test = coordinate;
		tests.push_back(sf::Vector2i(test));
	}
	//NG_LOG_ERROR("Starting FrOM:", start_.x, " ", start_.y);
	// start_ = position_;
}
