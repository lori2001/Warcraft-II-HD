#pragma once
#include "SFML/Graphics.hpp"

class Player {
public:
	enum Race {
		Orcs = 0,
		Humans
	};

	enum Difficulty {
		Easy = 0,
		Medium,
		Hard,
		User
	};

	enum Team {
		Team1 = 0, Team2,  Team3,  Team4,
		Team5,     Team6,  Team7,  Team8,
		Team9,     Team10, Team11, Team12
	};

	std::string title_;
	Race race_;
	Difficulty difficulty_;
	Team team_;
	sf::Color color_;
};