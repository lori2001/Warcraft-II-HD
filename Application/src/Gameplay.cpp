#include "Gameplay.h"

Gameplay::Gameplay()
{
	Map::setup({ 0, 0 }, Map::MAP_TYPE::NORMAL, mapScale_);

	gameView_.setViewport(viewportPercent_);
	updateViewMargins();

	// 62.0F, 57.0F, 1527.0F, 735.0F
	minimap_.setup({ 62.0F, 57.0F }, { 331.0F, 288.0F });
	minimap_.adjustScreenMark(gameView_.getSize(), gameView_.getCenter());

	test = new Barracks{ { 5, 6 } };
}

void Gameplay::handleEvents(const sf::Event& event)
{
	bool zoomIn = zoomInEvent(event);
	bool zoomOut = zoomOutEvent(event);
	if (zoomIn || zoomOut) // if zoom is triggered and either
	{
		float actualZoomFactor = viewZoomFactor_;

		if (zoomOut) // invert in case of zoom out
			actualZoomFactor = 1 / actualZoomFactor;

		viewCurrentZoomFactor_ *= actualZoomFactor; // keep in mind the current level of zooming
		gameView_.zoom(actualZoomFactor); // actually zoom the view

		updateViewMargins();
		// if out of bounds do not scale(AKA revert changes)
		if (gameView_.getCenter().x < topLeftMapMargin_.x ||
			gameView_.getCenter().x > botRightMapMargin_.x ||
			gameView_.getCenter().y < topLeftMapMargin_.y ||
			gameView_.getCenter().y > botRightMapMargin_.y)
		{
			actualZoomFactor = 1 / actualZoomFactor;
			viewCurrentZoomFactor_ *= actualZoomFactor;
			gameView_.zoom(actualZoomFactor);
			updateViewMargins();
		}

		minimap_.adjustScreenMark(gameView_.getSize(), gameView_.getCenter());
	}

	gameMappedMouse_ = {
		(ng::Cursor::getPosition().x - viewportPixel_.left) * viewCurrentZoomFactor_ + (gameView_.getCenter().x - topLeftMapMargin_.x),
		(ng::Cursor::getPosition().y - viewportPixel_.top) * viewCurrentZoomFactor_ + (gameView_.getCenter().y - topLeftMapMargin_.y)};

	if (ng::Cursor::getPosition().x < viewportPixel_.left || ng::Cursor::getPosition().y < viewportPixel_.top) {
		gameMappedMouse_ = { -10000.0F, -10000.0F };
	}

	// in-game entity events
	test->handleEvents(event, gameMappedMouse_);

}

void Gameplay::update()
{



	if (ng::Main::windowHasFocus())
	{
		// --- View movement --------------------------------------------------
		if (sf::Keyboard::isKeyPressed(keyNavigateLeft_) && gameView_.getCenter().x > topLeftMapMargin_.x)
		{
			gameView_.move({ -viewMoveSpeed_ * viewCurrentZoomFactor_ * ng::Timer::getDeltaTime(), 0 });
			minimap_.adjustScreenMark(gameView_.getSize(), gameView_.getCenter());
		}
		if (sf::Keyboard::isKeyPressed(keyNavigateRight_) && gameView_.getCenter().x < botRightMapMargin_.x)
		{
			gameView_.move({ viewMoveSpeed_ * viewCurrentZoomFactor_ * ng::Timer::getDeltaTime(), 0 });
			minimap_.adjustScreenMark(gameView_.getSize(), gameView_.getCenter());
		}
		if (sf::Keyboard::isKeyPressed(keyNavigateUp_) && gameView_.getCenter().y > topLeftMapMargin_.y)
		{
			gameView_.move({ 0, -viewMoveSpeed_ * viewCurrentZoomFactor_ * ng::Timer::getDeltaTime() });
			minimap_.adjustScreenMark(gameView_.getSize(), gameView_.getCenter());
		}
		if (sf::Keyboard::isKeyPressed(keyNavigateDown_) && gameView_.getCenter().y < botRightMapMargin_.y)
		{
			gameView_.move({ 0, viewMoveSpeed_ * viewCurrentZoomFactor_ * ng::Timer::getDeltaTime() });
			minimap_.adjustScreenMark(gameView_.getSize(), gameView_.getCenter());
		}
		// --------------------------------------------------------------------
	}
}

void Gameplay::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	ng::Main::setWindowView(gameView_);

	Map::draw(target, states);
	target.draw(*test);

	// resets view to default internally
	target.draw(minimap_); // ng::Main::applyDefaultViewToWindow();
}

Gameplay::~Gameplay()
{
}

void Gameplay::updateViewMargins()
{
	topLeftMapMargin_ = { gameView_.getSize().x / 2, gameView_.getSize().y / 2 };
	botRightMapMargin_ = { Map::getScaledSize().x - gameView_.getSize().x / 2 ,
						   Map::getScaledSize().y - gameView_.getSize().y / 2 };
}
