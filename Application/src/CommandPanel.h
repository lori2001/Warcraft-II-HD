#pragma once
#include "NGin.h"

enum class OPTIONS {
	WORKER
};

class CommandPanel : public sf::Drawable {

public:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void handleEvents(const sf::Event& event);
	
	sf::RectangleShape icons_;
	sf::FloatRect area_{10.0F, 370.0F, 432.0F, 615.0F};
};