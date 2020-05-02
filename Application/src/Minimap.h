#pragma once
#include "NGin.h"
#include "Map.h"
#include "SettingsFile.h"
#include "Style.h"

// not really a level, just behaves like it
class Minimap : public ng::Level {
public:
	// has to set up after being constructed
	void setup();

	void handleEvents(const sf::Event& event);
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void adjustScreenMark(const sf::Vector2f& viewSize, const sf::Vector2f& viewCenterPos);
private:
	// distance between margins of window and actual viewport
	const sf::FloatRect viewportPixel_{
	62.0F, 57.0F, 1527.0F, 735.0F
	};
	// compute proportional viewport values
	const sf::FloatRect viewportPercent_{
		viewportPixel_.left / MAIN_VIEW_WIDTH,
		viewportPixel_.top / MAIN_VIEW_HEIGHT,
		1.0F - (viewportPixel_.left + viewportPixel_.width) / MAIN_VIEW_WIDTH,
		1.0F - (viewportPixel_.top + viewportPixel_.height) / MAIN_VIEW_HEIGHT,
	};

	const sf::Vector2f viewSize_{
		MAIN_VIEW_WIDTH - viewportPixel_.left - viewportPixel_.width,
		MAIN_VIEW_HEIGHT - viewportPixel_.top - viewportPixel_.height
	};
	sf::View minimapView_{ sf::FloatRect{ 0, 0, viewSize_.x, viewSize_.y }};

	sf::RectangleShape screenMark_;
	const float screenMarkOutlineThickness = -3.5F; // thickness independent of view size
	const sf::Color screenMarkColor_ = sf::Color::Yellow;
};
