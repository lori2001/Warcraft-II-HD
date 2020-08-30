#pragma once
#include "NGin.h"

class GameEntity {
public:
	GameEntity() {
		entityId_ = entityIdEnumerator;
		entityIdEnumerator++;
	}

	int getId() { return entityId_; }

	sf::Vector2f getSpawnLocation() {
		return spawnLocation_;
	}


protected:
	sf::RectangleShape shape_;

	// MUST BE INITIALIZED BY CHILD
	sf::Vector2f spawnLocation_;
	

private:
	inline static int entityIdEnumerator = 0;
	int entityId_;
};