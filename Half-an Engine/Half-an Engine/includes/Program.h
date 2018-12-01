#pragma once
#include "SFML\Graphics.hpp"
#include "Window.h"
#include "RW\Paths.h"
#include "RW\FileReader.h"
#include "Sections\MainView.h"
#include "Sections\Toolbar.h"

class Program {
private:
	sf::Vector2f mouse; //holds position of the mouse

	RW::Paths paths;
	RW::FileReader filereader;
	Window window;

	Sections::MainView mainView;
	Sections::Toolbar toolbar;
public:
	void Setup(Window &window);
	void handleInput(Window &window);
	void Update(Window &window);
	void Compose(Window &window);
};