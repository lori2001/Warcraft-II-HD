#include "GameLevel.h"

GameLevel::GameLevel()
{
	GameDetailsFile::load();

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
	else {
		gameplay_.handleEvents(event);
	}
}

void GameLevel::update()
{
	if (gameMenu_ != nullptr)
	{
		gameMenu_->update();
	}
	else
	{
		gameplay_.update();
	}
}

void GameLevel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// menu elements
	target.draw(interface_);
	target.draw(menuButton_);

	// game view elements
	target.draw(gameplay_);

	// menu elements
	if (gameMenu_ != nullptr) {
		target.draw(*gameMenu_);
	}
}

GameLevel::~GameLevel()
{
	delete gameMenu_;
}

