#pragma once
#define MAIN_LEVEL

#include "NGin.h"

#include "Style.h"
#include "SettingsFile.h"

// Levels
#include "Levels.h"
#include "MenuLevel.h"
#include "LobbyLevel.h"
#include "SettingsLevel.h"
#include "EditorLevel.h"
#include "GameLevel.h"

// Do not print on release(closed) console
/*
#ifndef _DEBUG
	#define NG_CONSOLE_NOPRINT
#endif
*/

class Application : public ng::Main
{
public:
	Application();
	~Application();

	void handleEvents();
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	void drawLoadingScreen();

	// --- window icon ---
	sf::Image icon_;

	// --- loading screen ---
	std::shared_ptr<sf::Texture> loadingScreenTexture_;
	sf::Sprite loadingScreen_;

	// --- level ---
	ng::Level* currentLevel_ = 0;
};

ng::Main* setMainLevel() {
	return new Application;
}