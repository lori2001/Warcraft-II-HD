#pragma once
#define MAIN_LEVEL

#include "NGin.h"

// File input
#include "Files/SettingsFile.h"

// Levels
#include "Levels/MenuLevel.h"
#include "Levels/LobbyLevel.h"
#include "Levels/SettingsLevel.h"
#include "Levels/EditorLevel.h"
#include "Levels/GameLevel.h"

// Do not print on release(closed) console
#ifndef _DEBUG
	#define NG_CONSOLE_NOPRINT
#endif

class Application : public ngin::MainLevel
{
public:
	Application();
	~Application();

	void setup();
	void handleEvents();
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	void drawLoadingScreen();

	// scalable sizes
	sf::View view_{ sf::FloatRect{0, 0, 1920, 1080} };

	std::shared_ptr<sf::SoundBuffer> cursorSound_;
	std::shared_ptr<sf::Texture> orcCursorTexture_;
	std::shared_ptr<sf::Texture> humanCursorTexture_;

	std::shared_ptr<sf::Texture> loadingScreenTexture_;
	sf::Sprite loadingScreen_;

	ngin::Level* currentLevel_;
	SettingsFile settingsFile_; // loads and saves settings to json
};

ngin::MainLevel* setMainLevel() {
	return new Application;
}