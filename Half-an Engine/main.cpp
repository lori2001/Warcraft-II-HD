#include <iostream>
//#include <stdlib.h>
#include "SFML\Graphics.hpp"
#include "../Warcraft II/includes/UI/Cursor.h"
#include "includes/RW/Paths.h"
#include "includes/RW/Loading.h"
#include "includes/Windows.h"

int main()
{
	//sf::RenderWindow window;
	//window.create(sf::VideoMode(800, 600), "Half-an Engine");

	sf::RectangleShape box{ sf::Vector2f(100,100) };
	box.setFillColor(sf::Color::Red);

	/*opens a dialog box where you should choose the game's loaction*/
	RW::Paths paths;
	paths.chooseGamePath();
	//std::cout << paths.getGamePath();

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