#include "GameMenu.h"

GameMenu::GameMenu()
{
	background_.setPosition({ 690, 150 });

	ng::centerTextInBounds(menuText_, background_.getGlobalBounds(), -300);
	menuText_.setFillColor({color::FONT_COLOR_R, color::FONT_COLOR_G ,color::FONT_COLOR_B });

	// --- Properties ---------------------------
	// gameSettings_.setupStrings();
	// settingsIsActive = false;
	// gameSettings_.setupSliders();
}

void GameMenu::handleEvents(const sf::Event& event)
{
	mainMenuButton_.handleEvents(event, ng::Cursor::getPosition());
	settingsButton_.handleEvents(event, ng::Cursor::getPosition());
	continueButton_.handleEvents(event, ng::Cursor::getPosition());
	exitButton_    .handleEvents(event, ng::Cursor::getPosition());

	// --- Responses -----------------------------
	/*if (settingsIsActive) {
		gameSettings_.handleEvents(event, ng::Cursor::getPosition());

		if (gameSettings_.getResponse() == GameSettings::RESPONSE::BACK) {
			settingsIsActive = false;
		}
	}
	else {*/
		if (mainMenuButton_.isActive()) {
			Levels::currentLevel = Levels::LEVEL_TYPES::MENU;
		}
		else if (exitButton_.isActive()) {
			ng::Main::closeWindow();
		}
		else if (settingsButton_.isActive()) {
			// settingsIsActive = true;
		}
		// continue button called separately
	
	//}
	// -------------------------------------------
}

void GameMenu::update()
{
}

void GameMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(background_);

	/*if (settingsIsActive) {
		target.draw(gameSettings_);
	}
	else {*/
		target.draw(menuText_);
		target.draw(settingsButton_);
		target.draw(continueButton_);
		target.draw(mainMenuButton_);
		target.draw(exitButton_);
	//}
}