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
	// ----- Navigation Properties START -------------
	const float editorMoveSpeed_ = 265.0F;
	const float editorZoomFactor_ = 1.12F;
	const float editorMaxZoomFactor_ = 1.8F;
	const float editorMinZoomFactor_ = 1.0F / 3.0F;
	float editorCurrentZoomFactor_ = 1.0F; // DO NOT CHANGE!

	sf::Keyboard::Key keyNavigateUp_ = sf::Keyboard::W;
	sf::Keyboard::Key keyNavigateDown_ = sf::Keyboard::S;
	sf::Keyboard::Key keyNavigateLeft_ = sf::Keyboard::A;
	sf::Keyboard::Key keyNavigateRight_ = sf::Keyboard::D;

	// if these functions are true the view will zoom in/out
	bool zoomInEvent(const sf::Event& event)
	{
		return event.type == sf::Event::MouseWheelMoved && event.mouseWheel.delta < 0 && editorCurrentZoomFactor_ < editorMaxZoomFactor_;
	}
	bool zoomOutEvent(const sf::Event& event)
	{
		return event.type == sf::Event::MouseWheelMoved && event.mouseWheel.delta > 0 && editorCurrentZoomFactor_ > editorMinZoomFactor_;
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
	void updateViewMargins();

	const sf::Vector2f mapScale_{ 2.0F, 2.0F };
	
	sf::RectangleShape test;
	sf::RectangleShape test2;
};