#include "SFML\Graphics.hpp"
#include "includes/RW/Settings.h"
#include "includes/RW/Loading.h"
#include "includes/RW/Environment.h"
#include "includes/Menu.h"
#include "includes/UI/Cursor.h"

int main()
{
	RW::Settings settings;
	//load settings
	settings.read();

	sf::RenderWindow window;
	//create a window with appropiate settings
	settings.setWindow(window);

	RW::Loading loading;
	//load textures and sounds
	loading.loadFiles(window, settings);

	RW::Environment env;
	//load version number
	env.read();

	//display version
	std::cout << "Version: " << env.getVersion() << std::endl;

	UI::Cursor cursor;
	cursor.setTexture(loading.cursorT);
	cursor.setScale(settings.get1000Scale());

	Menu menu;
	menu.Setup(window);

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			//insert input handling in here
			menu.handleInput(window,event);

			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		//insert drawing commands in here

		//contains frame-by-frame logic
		menu.Update(window);
		//contains drawing commands
		menu.Compose(window);

		//set position of cursor
		cursor.setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
		//draw cursor
		window.draw(cursor);

		window.display();
	}

	//save settings on exit
	settings.save();

	return 0;
}