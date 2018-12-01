#include <iostream>
#include "SFML\Graphics.hpp"
#include "includes/RW/Environment.h"
#include "includes/UI/Cursor.h"
#include "includes/RW/Paths.h"
#include "includes/RW/Loading.h"
#include "includes/Window.h"
#include "includes/Program.h"

int main()
{
	RW::Environment env;
	//load version number and add +1 to build
	env.read();

	//display version
	std::cout << "Version: " << env.getVersion() << std::endl;

	/*opens a dialog box where the user should choose the game's location*/
	RW::Paths paths;
	if (!paths.chooseGamePath()) {
		return 0;
	}

	Window window;
	window.create(sf::VideoMode(800, 600), "Half-an Engine");

	RW::Loading loading;
	loading.loadFiles(window);

	Program program;
	program.Setup(window);

	UI::Cursor cursor;

	while (window.isOpen())
	{
		program.handleInput(window);

		window.clear(sf::Color::Color(60, 60, 60, 255));

		program.Update(window);
		program.Compose(window);

		window.display();
	}

	return 0;
}