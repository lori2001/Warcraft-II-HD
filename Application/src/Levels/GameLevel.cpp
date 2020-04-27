/*#include "GameLevel.h"

GameLevel::GameLevel()
{
	// --- Load Textures ------------------------
	interfaceTexture_ = ng::Resources::AcquireTexture("images/ui/interface.png");
	buttonTexture_ = ng::Resources::AcquireTexture("images/ui/button.png");
	warcraftFont_ = ng::Resources::AcquireFont("fonts/warcraft.ttf");
	// ------------------------------------------

	// --- Faction Styles -----------------------
	if (GameDetails::players[0].race_ == Player::Race::Humans) {
		ng::Cursor::setTexture(*ng::Resources::AcquireTexture("images/ui/human_cursor.png"));
		Music::playTheme(Music::Theme::HumanTheme);
	}
	else if (GameDetails::players[0].race_ == Player::Race::Orcs) {
		ng::Cursor::setTexture(*ng::Resources::AcquireTexture("images/ui/orc_cursor.png"));
		Music::playTheme(Music::Theme::OrcTheme);
	}
	// ------------------------------------------

	// --- Set Textures -------------------------
	interface_.setTexture(*interfaceTexture_);
	menuButton_.setTexture(*buttonTexture_);
	// ------------------------------------------

	// --- Set Positions ------------------------
	menuButton_.setPosition({ 20, 1010 });
	// ------------------------------------------

	// --- Set Scales ---------------------------
	menuButton_.setScale({ 0.55F, 1.0F });
	// ------------------------------------------

	// --- Setup Styles -------------------------
	setupUIStyle(*warcraftFont_, 40, sf::Color::Yellow);
	// ------------------------------------------
}

void GameLevel::handleEvents(const sf::Event& event)
{
	Levels::event = Levels::EVENT::EVENT_NONE;

	menuButton_.handleEvents(event, ng::Cursor::getPosition());

	if (menuButton_.isActive())
	{
		menuIsActive = !menuIsActive;

		//if (menuIsActive) {
		//	menu_ = new GameMenu;
		//}
		//else {
		//	delete menu_;
		//}
	}
}

void GameLevel::update()
{
}

void GameLevel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(interface_);
	target.draw(menuButton_);

	target.draw(unit);

	//if (menuIsActive)
	//	target.draw(*menu_);
}

void GameLevel::setupUIStyle(const sf::Font& font, const unsigned fontSize, const sf::Color& themeColor)
{
	menuButton_.setFont(font);
	menuButton_.setCharacterSize(fontSize);
	menuButton_.setTextColor(themeColor);
	menuButton_.setSelectColor(themeColor);
}*/
