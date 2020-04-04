#include "Application.h"

Levels::EVENT Levels::event = Levels::EVENT::EVENT_NONE;

Application::Application()
{
	settingsFile_.load();

	// Names of windows
	windowName = "Warcraft II HD"; // render window
	ng::Console::setName("Warcraft II HD"); // console window

	// Load in settings
	windowVideoMode = settingsFile_.getVideoMode();
	windowType = settingsFile_.getWindowType();

	ng::Audio::setMusicVolume(settingsFile_.getMusicVolume());
	ng::Audio::setSoundVolume(settingsFile_.getSoundVolume());

	// there is no reason to go above 60fps
	// window_.setFramerateLimit(60);

	// load and set icon file
	setWindowIcon("icon.png");

	// set default resource folder
	ng::Resources::setLocation("assets/");

	// load and draw loadingscreen
	loadingScreenTexture_ = ng::Resources::AcquireTexture("images/ui/loadingscreen.jpg");
	loadingScreen_.setTexture(*loadingScreenTexture_);
	drawLoadingScreen();

	// set up cursor sound
	cursorSound_ = ng::Resources::AcquireSoundBuffer("audio/click.wav");
	ng::Cursor::setBuffer(*cursorSound_);

	// load textures and make sure they never delete
	orcCursorTexture_ = ng::Resources::AcquireTexture("images/ui/orc_cursor.png");
	humanCursorTexture_ = ng::Resources::AcquireTexture("images/ui/human_cursor.png");

	// subscribe already loaded sounds to their types
	ng::Audio::subscribeSound(ng::Cursor::getSoundPtr());
	ng::Audio::subscribeMusic(&Music::nowPlaying_);

	// set menu as the first active level
	currentLevel_ = new MenuLevel;
}

// called when closing window
Application::~Application()
{
	// update settings before saving
	settingsFile_.setVideoMode(windowVideoMode);
	settingsFile_.setWindowType(windowType);
	settingsFile_.setMusicVolume(ng::Audio::getMusicVolume());
	settingsFile_.setSoundVolume(ng::Audio::getSoundVolume());

	settingsFile_.save(); // save settings
	delete currentLevel_; // delete current level responsibly
}

void Application::handleEvents()
{
	if (ng::Main::windowHasFocus())
	{
		// handle the events of whatever the current level
		currentLevel_->handleEvents(event_);

		switch (Levels::event)
		{
		case Levels::EVENT::EVENT_LOBBY:
			delete currentLevel_;
			currentLevel_ = new LobbyLevel;
			break;

		case Levels::EVENT::EVENT_SETTINGS:
			delete currentLevel_;
			currentLevel_ = new SettingsLevel;
			break;
		case Levels::EVENT::EVENT_EDITOR:
			drawLoadingScreen(); // slower loading expected

			delete currentLevel_;
			currentLevel_ = new EditorLevel;

			ng::Resources::destroyUnused(); // destroy menu resources
			break;

		case Levels::EVENT::EVENT_GAME:
			drawLoadingScreen(); // slower loading expected

			delete currentLevel_;
			currentLevel_ = new GameLevel;

			ng::Resources::destroyUnused(); // destroy menu resources
			break;

			// smooth menu loading
		case Levels::EVENT::EVENT_MENU:
			drawLoadingScreen(); // slower loading expected

			delete currentLevel_;
			// compromise: loads menu slower but later settings faster
			ng::Resources::destroyUnused();

			currentLevel_ = new MenuLevel;
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
	ng::Main::view.reset(sf::FloatRect{ 0, 0, 1920, 1080 }); // reset moved view
	ng::Main::applyViewToWindow();

	window.draw(loadingScreen_);
	window.display();
}
