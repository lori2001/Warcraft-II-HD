#include <iostream>
#include "SFML\Graphics.hpp"
#include "includes/RW/Environment.h"
#include "../Warcraft II/includes/UI/Cursor.h"
#include "includes/RW/Paths.h"
#include "includes/RW/Loading.h"
#include "includes/Windows.h"

int main()
{
	RW::Environment env;
	//load version number and add +1 to build
	env.read();

	//display version
	std::cout << "Version: " << env.getVersion() << std::endl;

	sf::RectangleShape box{ sf::Vector2f(100,100) };
	box.setFillColor(sf::Color::Red);

	/*opens a dialog box where the user should choose the game's location*/
	RW::Paths paths;
	if (!paths.chooseGamePath()) {
		return 0;
	}

	MainWindow window;
	//window.createWindow(sf::VideoMode(800, 600), "Half-an Engine");
	window.createWindow(sf::VideoMode(800, 600));

	RW::Loading loading;
	loading.loadFiles(window);

	UI::Cursor cursor;

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			//insert input handling in here

			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::Resized)
			{
				sf::FloatRect visibleArea( 0, 0,(float)event.size.width, (float)event.size.height);
				window.setView(sf::View(visibleArea));
				window.onResize(visibleArea);
				//box.setScale(window.get1920Scale());
			}
		}

		window.clear(sf::Color::Color(60, 60, 60, 255));

		//insert drawing commands in here
		window.draw(box);

		window.display();
	}

	return 0;
}