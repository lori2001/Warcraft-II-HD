#pragma once
#include "NGin.h"

#include "Map.h"
#include "SettingsFile.h"
#include "Style.h"

class GameViewport : public ng::Level {
public:
	GameViewport();

	void handleEvents(const sf::Event& event);
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	~GameViewport();
private:
	// distance between screen endpoints and viewport in pixels
	const sf::FloatRect viewportPixel_ {
		455.0F, 35.0F, 42.0F, 34.0F
	};

	const sf::FloatRect viewportPercent_ {
		viewportPixel_.left / MAIN_VIEW_WIDTH,
		viewportPixel_.top / MAIN_VIEW_HEIGHT,
		1.0F - (viewportPixel_.left + viewportPixel_.width) / MAIN_VIEW_WIDTH,
		1.0F - (viewportPixel_.top + viewportPixel_.height) / MAIN_VIEW_HEIGHT,
	};
	
	sf::View gameView_{ sf::FloatRect{
		0, 0,
		MAIN_VIEW_WIDTH - viewportPixel_.left - viewportPixel_.width,
		MAIN_VIEW_HEIGHT - viewportPixel_.top - viewportPixel_.height }
	};

	const sf::Vector2f mapScale_{ 2.0F, 2.0F };
	
	sf::RectangleShape test;
	sf::RectangleShape test2;
};