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
		bool windowed = false;
		Window win1;

	/*opens a dialog box where the user should choose the game's location*/
	RW::Paths paths;
	if (!paths.chooseGamePath()) {
		return 0;
	}

	MainWindow window;
	window.create(sf::VideoMode(800, 600), "Half-an Engine");

	RW::Loading loading;
	loading.loadFiles(window);

	UI::Cursor cursor;

	while (window.isOpen())
	{
		sf::Event event;
			sf::Event event1;

			while (win1.pollEvent(event1))
			{
				if (event1.type == sf::Event::MouseButtonReleased) {
					windowed = false;
					win1.close();
				}

				if (event1.type == sf::Event::Closed)
					win1.close();
			}

			win1.clear(sf::Color::Color(60, 60, 60, 255));
			win1.draw(box);
			win1.display();

		while (window.pollEvent(event))
		{
			//insert input handling in here
				if (event.type == sf::Event::MouseButtonReleased ) 
				{
					win1.create(sf::VideoMode(200, 200));
					windowed = true;
				}

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

			if(!windowed)
			//insert drawing commands in here
			window.draw(box);

		window.display();
	}

	return 0;
}