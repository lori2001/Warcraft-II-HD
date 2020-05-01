#include "GameViewport.h"

GameViewport::GameViewport()
{
	Map::setup({ 0, 0 }, Map::MAP_TYPE::NORMAL, mapScale_);

	gameView_.setViewport(viewportPercent_);
	updateViewMargins();
}

void GameViewport::handleEvents(const sf::Event& event)
{
	bool zoomIn = zoomInEvent(event);
	bool zoomOut = zoomOutEvent(event);
	if (zoomIn || zoomOut) // if zoom is triggered and either
	{
		float actualZoomFactor = editorZoomFactor_;

		if (zoomOut) // invert in case of zoom out
			actualZoomFactor = 1 / actualZoomFactor;

		editorCurrentZoomFactor_ *= actualZoomFactor; // keep in mind the current level of zooming
		gameView_.zoom(actualZoomFactor); // actually zoom the view

		updateViewMargins();
		// if out of bounds do not scale(AKA revert changes)
		if (gameView_.getCenter().x < topLeftMapMargin_.x ||
			gameView_.getCenter().x > botRightMapMargin_.x ||
			gameView_.getCenter().y < topLeftMapMargin_.y ||
			gameView_.getCenter().y > botRightMapMargin_.y)
		{
			actualZoomFactor = 1 / actualZoomFactor;
			editorCurrentZoomFactor_ *= actualZoomFactor;
			gameView_.zoom(actualZoomFactor);
			updateViewMargins();
		}
	}
}

void GameViewport::update()
{
	if (ng::Main::windowHasFocus())
	{
		// --- View movement --------------------------------------------------
		const sf::Vector2f posBefore = gameView_.getCenter();
		if (sf::Keyboard::isKeyPressed(keyNavigateLeft_) && gameView_.getCenter().x > topLeftMapMargin_.x)
		{
			gameView_.move({ -editorMoveSpeed_ * editorCurrentZoomFactor_ * ng::Timer::getDeltaTime(), 0 });
		}
		if (sf::Keyboard::isKeyPressed(keyNavigateRight_) && gameView_.getCenter().x < botRightMapMargin_.x)
		{
			gameView_.move({ editorMoveSpeed_ * editorCurrentZoomFactor_ * ng::Timer::getDeltaTime(), 0 });
		}
		if (sf::Keyboard::isKeyPressed(keyNavigateUp_) && gameView_.getCenter().y > topLeftMapMargin_.y)
		{
			gameView_.move({ 0, -editorMoveSpeed_ * editorCurrentZoomFactor_ * ng::Timer::getDeltaTime() });
		}
		if (sf::Keyboard::isKeyPressed(keyNavigateDown_) && gameView_.getCenter().y < botRightMapMargin_.y)
		{
			gameView_.move({ 0, editorMoveSpeed_ * editorCurrentZoomFactor_ * ng::Timer::getDeltaTime() });
		}
		// --------------------------------------------------------------------
	}
}

void GameViewport::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	ng::Main::setWindowView(gameView_);
	Map::draw(target, states);

	ng::Main::applyDefaultViewToWindow();
}

GameViewport::~GameViewport()
{
}

void GameViewport::updateViewMargins()
{
	topLeftMapMargin_ = { gameView_.getSize().x / 2, gameView_.getSize().y / 2 };
	botRightMapMargin_ = { Map::getScaledSize().x - gameView_.getSize().x / 2 ,
						   Map::getScaledSize().y - gameView_.getSize().y / 2 };
}
