#pragma once
#include "NGin.h"

class GameScreen : public ngin::Level  {
	sf::FloatRect windowRect_{};
	sf::Vector2f tileSize_{ 32,32 };
};