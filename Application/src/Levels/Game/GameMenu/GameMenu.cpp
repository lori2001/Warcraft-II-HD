#include "GameMenu.h"

GameMenu::GameMenu()
{
	// --- Load Textures ------------------------
	buttonTexture_     = ng::Resources::AcquireTexture("images/ui/button.png");
	backgroundTexture_ = ng::Resources::AcquireTexture("images/ui/orc_clay_bg.png");
	sliderTexture_     = ng::Resources::AcquireTexture("images/ui/slider.png");
	warcraftFont_      = ng::Resources::AcquireFont("fonts/warcraft.ttf");
	// ------------------------------------------

	// --- Set Textures -------------------------
	background_    .setTexture(*backgroundTexture_);
	settingsButton_.setTexture(*buttonTexture_);
	mainMenuButton_.setTexture(*buttonTexture_);
	continueButton_.setTexture(*buttonTexture_);
	exitButton_    .setTexture(*buttonTexture_);
	gameSettings_.setTextures(*sliderTexture_, *buttonTexture_);
	// ------------------------------------------

	// --- Set Strings --------------------------
	menuText_.setString("In-Game Menu");
	gameSettings_.setupStrings();
	// ------------------------------------------

	// --- Set Scales ---------------------------
	settingsButton_.setScale({ 1.0F, 1.25F });
	continueButton_.setScale({ 1.0F, 1.25F });
	mainMenuButton_.setScale({ 1.0F, 1.25F });
	exitButton_    .setScale({ 1.0F, 1.25F });
	gameSettings_  .setScales({ 1.0F, 1.25F });
	// ------------------------------------------
	
	// -- Setup Styles --------------------------
	setupUIStyle(*warcraftFont_, 40, sf::Color::Yellow);
	// ------------------------------------------

	// --- Set Positions ------------------------
	// background size: 540x780
	background_    .setPosition({ 690, 150 });
	continueButton_.setPosition({ 745, 330 });
	settingsButton_.setPosition({ 745, 430 });
	mainMenuButton_.setPosition({ 745, 730 });
	exitButton_    .setPosition({ 745, 830 });
	
	ng::centerTextInBounds(menuText_, background_.getGlobalBounds(), -300);
	gameSettings_.setPositionOn(background_);
	// ------------------------------------------

	// --- Properties ---------------------------
	settingsIsActive = false;
	gameSettings_.setupSliders();
}

void GameMenu::handleEvents(const sf::Event& event)
{
	mainMenuButton_.handleEvents(event, ng::Cursor::getPosition());
	settingsButton_.handleEvents(event, ng::Cursor::getPosition());
	continueButton_.handleEvents(event, ng::Cursor::getPosition());
	exitButton_    .handleEvents(event, ng::Cursor::getPosition());

	// --- Responses -----------------------------
	if (settingsIsActive) {
		gameSettings_.handleEvents(event, ng::Cursor::getPosition());

		if (gameSettings_.getResponse() == GameSettings::RESPONSE::BACK) {
			settingsIsActive = false;
		}
	}
	else {
		if (mainMenuButton_.isActive()) {
			Levels::event = Levels::EVENT::EVENT_MENU;
		}
		else if (exitButton_.isActive()) {
			ng::Main::closeWindow();
		}
		else if (settingsButton_.isActive()) {
			settingsIsActive = true;
		}
		else if (continueButton_.isActive()) {
			// Levels::event = Levels::EVENT::EVENT_MENU;
		}
		else {
			Levels::event = Levels::EVENT::EVENT_NONE;
		}
	}
	// -------------------------------------------
}

void GameMenu::update()
{
}

void GameMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(background_);

	if (settingsIsActive) {
		target.draw(gameSettings_);
	}
	else {
		target.draw(menuText_);
		target.draw(settingsButton_);
		target.draw(continueButton_);
		target.draw(mainMenuButton_);
		target.draw(exitButton_);
	}
}

void GameMenu::setupUIStyle(const sf::Font& font, const unsigned fontSize, const sf::Color& themeColor)
{
	continueButton_.setFont(font);
	continueButton_.setCharacterSize(fontSize);
	continueButton_.setTextColor(themeColor);
	continueButton_.setSelectColor(themeColor);

	mainMenuButton_.setFont(font);
	mainMenuButton_.setCharacterSize(fontSize);
	mainMenuButton_.setTextColor(themeColor);
	mainMenuButton_.setSelectColor(themeColor);

	exitButton_.setFont(font);
	exitButton_.setCharacterSize(fontSize);
	exitButton_.setTextColor(themeColor);
	exitButton_.setSelectColor(themeColor);

	settingsButton_.setFont(font);
	settingsButton_.setCharacterSize(fontSize);
	settingsButton_.setTextColor(themeColor);
	settingsButton_.setSelectColor(themeColor);

	menuText_.setFont(font);
	menuText_.setCharacterSize(static_cast<unsigned>(1.5F * fontSize));
	menuText_.setFillColor(themeColor);

	gameSettings_.setupUIStyle(font , fontSize, themeColor);
}
