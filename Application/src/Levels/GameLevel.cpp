#include "GameLevel.h"

void GameLevel::setup()
{
	// --- Load Textures ------------------------
	interfaceTexture_ = ngin::Resources::AcquireTexture("images/ui/interface.png");
	buttonTexture_ = ngin::Resources::AcquireTexture("images/ui/button.png");
	warcraftFont_ = ngin::Resources::AcquireFont("fonts/warcraft.ttf");
	// ------------------------------------------

	// --- Faction Styles -----------------------
	if (GameDetails::players[0].race_ == Player::Race::Humans) {
		ngin::Cursor::setTexture(*ngin::Resources::AcquireTexture("images/ui/human_cursor.png"));
		Music::playTheme(Music::Theme::HumanTheme);
	}
	else if (GameDetails::players[0].race_ == Player::Race::Orcs) {
		ngin::Cursor::setTexture(*ngin::Resources::AcquireTexture("images/ui/orc_cursor.png"));
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
	menuButton_.handleEvents(event, ngin::Cursor::getPosition());

	if (menuButton_.isActive())
	{
		menuIsActive = !menuIsActive;

		if (menuIsActive) {
			menu_ = new GameMenu;
		}
		else {
			delete menu_;
		}
	}

	if (menuIsActive) {
		menu_->handleEvents(event);

		// --- Responses -----------------------------
		response_ = menu_->getResponse(); // forward gameMenu's responses

		if (response_ == GameMenu::CONTINUE) {
			menuIsActive = false;
		}
		// -------------------------------------------
	}

	testSoldier.handleEvents(event, ngin::Cursor::getPosition());
}

void GameLevel::update()
{
	testSoldier.animate(ngin::Timer::getDeltaTime());
}

void GameLevel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(interface_);
	target.draw(menuButton_);

	if (menuIsActive)
		target.draw(*menu_);

	target.draw(testSoldier);
}

void GameLevel::setupUIStyle(const sf::Font& font, const unsigned fontSize, const sf::Color& themeColor)
{
	menuButton_.setFont(font);
	menuButton_.setCharacterSize(fontSize);
	menuButton_.setTextColor(themeColor);
	menuButton_.setSelectColor(themeColor);
}
