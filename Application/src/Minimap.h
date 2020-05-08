#pragma once
#include "NGin.h"
#include "Map.h"
#include "SettingsFile.h"
#include "Style.h"

// not really a level, just behaves like it
class Minimap : public ng::Level {
public:
	// has to set up after being constructed
	void setup(const sf::Vector2f position, const sf::Vector2f size);

	void handleEvents(const sf::Event& event);
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void adjustScreenMark(const sf::Vector2f& viewSize, const sf::Vector2f& viewCenterPos);
private:
	// distance between margins of window and actual viewport
	sf::View minimapView_;

	sf::RectangleShape screenMark_;
	const float screenMarkOutlineThickness = -3.5F; // thickness independent of view size
	const sf::Color screenMarkColor_ = sf::Color::Yellow;
};
