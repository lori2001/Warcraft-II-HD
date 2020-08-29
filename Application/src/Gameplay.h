#pragma once
#include "NGin.h"

#include "Map.h"
#include "Minimap.h"

#include "SettingsFile.h"
#include "Style.h"

#include "Barracks.h"

#include "CommandPanel.h"

class Gameplay : public sf::Drawable {
public:
	Gameplay();

	void handleEvents(const sf::Event& event, CommandPanel& commandPanel);
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::View getView() const { return gameView_; }

	sf::FloatRect getGlobalBounds() const {
		return {
			viewportPixel_.left, viewportPixel_.top,
			MAIN_VIEW_WIDTH - viewportPixel_.left - viewportPixel_.width,
			MAIN_VIEW_HEIGHT - viewportPixel_.top - viewportPixel_.height };
	}

	~Gameplay();
private:
	// ----- Navigation Properties START -------------
	const float viewMoveSpeed_ = 265.0F;
	const float viewZoomFactor_ = 1.12F;
	const float viewMaxZoomFactor_ = 1.2F; // farthest
	const float viewMinZoomFactor_ = 1.0F / 2.6F; // closest
	float viewCurrentZoomFactor_ = 1.0F; // DO NOT CHANGE!

	sf::Keyboard::Key keyNavigateUp_ = sf::Keyboard::W;
	sf::Keyboard::Key keyNavigateDown_ = sf::Keyboard::S;
	sf::Keyboard::Key keyNavigateLeft_ = sf::Keyboard::A;
	sf::Keyboard::Key keyNavigateRight_ = sf::Keyboard::D;

	// if these functions are true the view will zoom in/out
	bool zoomInEvent(const sf::Event& event)
	{
		return event.type == sf::Event::MouseWheelMoved && event.mouseWheel.delta < 0 && viewCurrentZoomFactor_ < viewMaxZoomFactor_;
	}
	bool zoomOutEvent(const sf::Event& event)
	{
		return event.type == sf::Event::MouseWheelMoved && event.mouseWheel.delta > 0 && viewCurrentZoomFactor_ > viewMinZoomFactor_;
	}
	// ----- Navigation Properties ENDD ----------------

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
	sf::Vector2f topLeftMapMargin_, botRightMapMargin_;

	sf::Vector2f gameMappedMouse_ = { 0,0 };

	void updateViewMargins();

	const sf::Vector2f mapScale_{ 2.0F, 2.0F };

	Minimap minimap_;

	Barracks* test;

	sf::RectangleShape selectRectangle_;
	bool shouldSelect_ = false;
};