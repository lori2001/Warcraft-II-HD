#include "Application.h"

Application::Application()
{
	settingsFile_.load();

	// Names of windows
	windowName_ = "Warcraft II HD"; // render window
	ngin::Console::setName("Warcraft II HD"); // console window

	// Load in settings
	windowVideoMode_ = settingsFile_.getVideoMode();
	windowType_ = settingsFile_.getWindowType();

	ngin::Audio::setMusicVolume(settingsFile_.getMusicVolume());
	ngin::Audio::setSoundVolume(settingsFile_.getSoundVolume());
}

// called when closing window
Application::~Application()
{
	// update settings before saving
	settingsFile_.setVideoMode(windowVideoMode_);
	settingsFile_.setWindowType(windowType_);
	settingsFile_.setMusicVolume(ngin::Audio::getMusicVolume());
	settingsFile_.setSoundVolume(ngin::Audio::getSoundVolume());

	settingsFile_.save(); // save settings
	delete currentLevel_; // delete current level responsibly
}

void Application::setup()
{
	// add view to window to support resizing
	window_.setView(view_);

	// there is no reason to go above 60fps
	window_.setFramerateLimit(60);

	// load and set icon file
	sf::Image icon;
	if (icon.loadFromFile("icon.png")) {
		window_.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	}
	else {
		NG_LOG_WARN("Failed to set Icon!");
	}

	// set default resource folder
	ngin::Resources::setLocation("assets/");

	// load and draw loadingscreen
	loadingScreenTexture_ = ngin::Resources::AcquireTexture("images/ui/loadingscreen.jpg");
	drawLoadingScreen();

	// set up cursor
	cursorSound_ = ngin::Resources::AcquireSoundBuffer("audio/click.wav");

	// make sure cursor textures never delete
	orcCursorTexture_ =  ngin::Resources::AcquireTexture("images/ui/orc_cursor.png");
	humanCursorTexture_ = ngin::Resources::AcquireTexture("images/ui/human_cursor.png");

	ngin::Cursor::setBuffer(*cursorSound_);
	ngin::Audio::subscribeSound(ngin::Cursor::getSoundPtr());
	ngin::Audio::subscribeMusic(&Music::nowPlaying_);

	// set menu as the first active level
	currentLevel_ = new MenuLevel;
}

void Application::handleEvents()
{
	currentLevel_->handleEvents(event_);

	// --- Menu Responses ---------------------------------------
	if (currentLevel_->getResponse() == MenuLevel::RESPONSE::START)
	{
		delete currentLevel_;
		currentLevel_ = new LobbyLevel;
	}
	else if (currentLevel_->getResponse() == MenuLevel::RESPONSE::OPTIONS)
	{
		delete currentLevel_;
		currentLevel_ = new SettingsLevel;

		currentLevel_->getFromWindow(windowVideoMode_, windowName_, windowType_);
	}
	else if (currentLevel_->getResponse() == MenuLevel::RESPONSE::EDITOR)
	{
		delete currentLevel_;
		currentLevel_ = new EditorLevel;
	}
	else if (currentLevel_->getResponse() == MenuLevel::RESPONSE::EXIT)
	{
		window_.close();
	}
	// ----------------------------------------------------------

	// --- Lobby Responses --------------------------------------
	if (currentLevel_->getResponse() == LobbyLevel::RESPONSE::BACK)
	{
		delete currentLevel_;
		currentLevel_ = new MenuLevel;
	}
	else if (currentLevel_->getResponse() == LobbyLevel::RESPONSE::PLAY)
	{
		drawLoadingScreen(); // slower loading expected

		delete currentLevel_;
		currentLevel_ = new GameLevel;

		ngin::Resources::destroyUnused(); // destroy menu resources
	}
	// ----------------------------------------------------------

	// --- Settings Responses -----------------------------------
	if (currentLevel_->getResponse() == SettingsLevel::RESPONSE::BACK)
	{
		delete currentLevel_;
		currentLevel_ = new MenuLevel;
	} // Settings::RESPONSE::APPLY gets checked upon in update()
	// ----------------------------------------------------------

	// --- Editor Responses -------------------------------------
	if (currentLevel_->getResponse() == EditorLevel::RESPONSE::BACK)
	{
		delete currentLevel_;
		currentLevel_ = new MenuLevel;
	}
	// ----------------------------------------------------------

	// --- GameMenu Responses -----------------------------------
	if (currentLevel_->getResponse() == GameMenu::RESPONSE::MAIN_MENU)
	{
		drawLoadingScreen(); // slower loading expected

		delete currentLevel_;
		// compromise: loads menu slower but later settings faster
		ngin::Resources::destroyUnused();

		currentLevel_ = new MenuLevel;
	}
	else if (currentLevel_->getResponse() == GameMenu::RESPONSE::EXIT)
	{
		window_.close();
	}
	// ----------------------------------------------------------
}

void Application::update()
{
	currentLevel_->update();

	// --- Settings Response ------------------------------------
	if (currentLevel_->getResponse() == SettingsLevel::RESPONSE::APPLY)
	{
		currentLevel_->changeWindow(windowVideoMode_, windowName_, windowType_);
	}
	// ----------------------------------------------------------
}

void Application::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*currentLevel_);
}

void Application::drawLoadingScreen()
{
	loadingScreen_.setTexture(*loadingScreenTexture_);
	window_.draw(loadingScreen_);
	window_.display();
}
