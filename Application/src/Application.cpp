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
	// there is no reason to go above 60fps
	window_.setFramerateLimit(60);

	// load and set icon file
	setWindowIcon("icon.png");

	// set default resource folder
	ngin::Resources::setLocation("assets/");

	// load and draw loadingscreen
	loadingScreenTexture_ = ngin::Resources::AcquireTexture("images/ui/loadingscreen.jpg");
	loadingScreen_.setTexture(*loadingScreenTexture_);
	drawLoadingScreen();

	// set up cursor sound
	cursorSound_ = ngin::Resources::AcquireSoundBuffer("audio/click.wav");
	ngin::Cursor::setBuffer(*cursorSound_);

	// load textures and make sure they never delete
	orcCursorTexture_ =  ngin::Resources::AcquireTexture("images/ui/orc_cursor.png");
	humanCursorTexture_ = ngin::Resources::AcquireTexture("images/ui/human_cursor.png");

	// subscribe already loaded sounds to their types
	ngin::Audio::subscribeSound(ngin::Cursor::getSoundPtr());
	ngin::Audio::subscribeMusic(&Music::nowPlaying_);

	// set menu as the first active level
	currentLevel_ = new MenuLevel;
}

void Application::handleEvents()
{
	if (ngin::MainLevel::windowHasFocus())
	{
		// handle the events of whatever the current level
		currentLevel_->handleEvents(event_);

		switch (currentLevel_->getResponse())
		{
		case MenuLevel::LOBBY:
			delete currentLevel_;
			currentLevel_ = new LobbyLevel;
			break;

		case MenuLevel::SETTINGS:
			delete currentLevel_;
			currentLevel_ = new SettingsLevel;
			break;
		case MenuLevel::EDITOR:
			drawLoadingScreen(); // slower loading expected

			delete currentLevel_;
			currentLevel_ = new EditorLevel;

			ngin::Resources::destroyUnused(); // destroy menu resources
			break;

		case LobbyLevel::GAME:
			drawLoadingScreen(); // slower loading expected

			delete currentLevel_;
			currentLevel_ = new GameLevel;

			ngin::Resources::destroyUnused(); // destroy menu resources
			break;

			// smooth menu loading
		case SettingsLevel::MAIN_MENU:
		case LobbyLevel::MAIN_MENU:
			delete currentLevel_;
			currentLevel_ = new MenuLevel;
			break;

			// heavy menu loading
		case EditorLevel::MAIN_MENU:
		case GameMenu::MAIN_MENU:
			drawLoadingScreen(); // slower loading expected

			delete currentLevel_;
			// compromise: loads menu slower but later settings faster
			ngin::Resources::destroyUnused();

			currentLevel_ = new MenuLevel;
			break;

		case GameMenu::EXIT:
		case MenuLevel::EXIT:
			window_.close();
			break;
		}
	}
}

void Application::update()
{
	currentLevel_->update();
}

void Application::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*currentLevel_);
}

void Application::drawLoadingScreen()
{
	// make sure view focuses on loading screen
	ngin::MainLevel::view_.reset(sf::FloatRect{ 0, 0, 1920, 1080 }); // reset moved view
	ngin::MainLevel::applyViewToWindow();

	window_.draw(loadingScreen_);
	window_.display();
}
