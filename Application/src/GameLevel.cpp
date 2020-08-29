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
	normalCursor_ = ng::Cursor::getShape();

	selectCursor_.setTexture(&*selectCursorTexture_);
	selectCursor_.setSize(sf::Vector2f{ selectCursorTexture_->getSize() });
	selectCursor_.setOrigin(ng::divVec(selectCursor_.getSize(), 2.0F));
	selectCursor_.setFillColor(sf::Color{ color::IN_GAME_SELECT_R, color::IN_GAME_SELECT_G, color::IN_GAME_SELECT_B });
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
		commandPanel_.handleEvents(event);
		gameplay_.handleEvents(event, commandPanel_);

		if (gameplay_.getGlobalBounds().contains(ng::Cursor::getPosition()) && event.type == sf::Event::MouseButtonPressed)
		{
			ng::Cursor::setShape(selectCursor_);
		}
		if (event.type == sf::Event::MouseButtonReleased) {
			ng::Cursor::setShape(normalCursor_);
		}
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

	// commands of given element
	target.draw(commandPanel_);

	// menu elements
	if (gameMenu_ != nullptr) {
		target.draw(*gameMenu_);
	}
}

GameLevel::~GameLevel()
{
	delete gameMenu_;
}

