#include "GameLevel.h"

GameLevel::GameLevel()
{
	// --- Faction Styles -----------------------
	if (GameDetailsFile::getPlayerRace() == GameDetailsFile::races_[2].string) {
		ng::Cursor::setTexture(NG_TEXTURE_SPTR("images/ui/human_cursor.png"));
		Music::playTheme(Music::Theme::HumanTheme);
	}
	else if (GameDetailsFile::getPlayerRace() == GameDetailsFile::races_[1].string) {
		ng::Cursor::setTexture(NG_TEXTURE_SPTR("images/ui/orc_cursor.png"));
		Music::playTheme(Music::Theme::OrcTheme);
	}
	// ------------------------------------------
}

void GameLevel::handleEvents(const sf::Event& event)
{
	menuButton_.handleEvents(event, ng::Cursor::getPosition());

	if (menuButton_.isActive() || menuTriggerEvent(event))
	{
		if (gameMenu_ == nullptr) {
			delete gameMenu_;
			gameMenu_ = new GameMenu;
		}
		else {
			delete gameMenu_;
			gameMenu_ = nullptr;
		}
	}

	if (gameMenu_ != nullptr) {
		gameMenu_->handleEvents(event);

		if (gameMenu_->shouldClose()) {
			delete gameMenu_;
			gameMenu_ = nullptr;
		}
	}

	gameViewport.handleEvents(event);
}

void GameLevel::update()
{
	if (gameMenu_ != nullptr) {
		gameMenu_->update();
	}

	gameViewport.update();
}

void GameLevel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(interface_);
	target.draw(menuButton_);

	if (gameMenu_ != nullptr) {
		target.draw(*gameMenu_);
	}

	target.draw(gameViewport);
}

GameLevel::~GameLevel()
{
	delete gameMenu_;
}

