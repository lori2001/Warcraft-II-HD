#include "Application.h"

Levels::LEVEL_TYPES Levels::currentLevel = Levels::LEVEL_TYPES::MENU;

Application::Application()
{
	// load settings
	SettingsFile::load();

	// Names of windows
	windowName = WINDOW_NAME; // render window
	ng::Console::setName(WINDOW_NAME); // console window

	// apply file settings
	windowVideoMode = SettingsFile::getVideoMode();
	windowType = SettingsFile::getWindowType();
	ng::Audio::setMusicVolume(SettingsFile::getMusicVolume());
	ng::Audio::setSoundVolume(SettingsFile::getSoundVolume());

	// load and set icon file
	setWindowIcon(location::ICON);

	// set default resource folder
	ng::Resources::setLocation(location::ASSETS);

	// load and draw loadingscreen
	loadingScreenTexture_ = NG_TEXTURE_SPTR(location::LOADING_SCREEN);
	loadingScreen_.setTexture(*loadingScreenTexture_);
	drawLoadingScreen();

	// set up cursor sound
	ng::Cursor::setBuffer(NG_SOUNDBUFFER_SPTR(location::CLICK_SOUND));

	// load textures and make sure they never delete
	ng::Cursor::setTexture(NG_TEXTURE_SPTR(location::ORC_CURSOR));

	// subscribe already loaded sounds to their types
	ng::Audio::subscribeSound(ng::Cursor::getSoundPtr());
	ng::Audio::subscribeMusic(&Music::nowPlaying_);

	// set menu as the first active level
	currentLevel_ = new MenuLevel;
}

// called when closing window
Application::~Application()
{
	SettingsFile::save(); // save settings
	delete currentLevel_; // delete current level responsibly
}

void Application::handleEvents()
{
	if (ng::Main::windowHasFocus())
	{
		// handle the events of whatever the current level
		currentLevel_->handleEvents(event_);

		Levels::checkForChanges();
		// if there is a level-event
		if (Levels::hasChanged())
		{
			drawLoadingScreen();

			if (Levels::changeComesFrom() == Levels::LEVEL_TYPES::EDITOR)
			{
				// show in-game cursor
				ng::Cursor::showTextured();
			}

			delete currentLevel_; // delete old level resources like a good boi
			switch (Levels::currentLevel) // assigne new level
			{
			case Levels::LEVEL_TYPES::LOBBY:
				GameDetailsFile::load();
				currentLevel_ = new LobbyLevel;
				break;
			case Levels::LEVEL_TYPES::SETTINGS:
				currentLevel_ = new SettingsLevel;
				break;
			case Levels::LEVEL_TYPES::EDITOR:
				currentLevel_ = new EditorLevel;
				break;
			case Levels::LEVEL_TYPES::GAME:
				currentLevel_ = new GameLevel;
				break;
			case Levels::LEVEL_TYPES::MENU:
				currentLevel_ = new MenuLevel;
				break;
			default:
				std::string error = "Level defined but no actual level connected to it in Application.cpp";
				NG_LOG_ERROR(error);
				throw(error);
				ng::Main::closeWindow();
			}

			ng::Resources::destroyUnused(); // destroy unused resources
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
	ng::Main::nginView_.reset(
		sf::FloatRect{ 0, 0, MAIN_VIEW_WIDTH, MAIN_VIEW_HEIGHT }); // reset moved view
	ng::Main::applyDefaultViewToWindow();

	window.draw(loadingScreen_);
	window.display();
}
