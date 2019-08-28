#pragma once
#include <vector>
#include "Player.h"
#include "../../Files/MapFile.h"

class GameDetails {
public:

	static MapFile mapFile;
	// 0->user 1-11->NPC's
	static std::vector<Player> players;
};