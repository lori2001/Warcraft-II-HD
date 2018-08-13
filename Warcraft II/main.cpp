#include "SFML\Graphics.hpp"
#include "includes/RW/Environment.h"
#include "includes/Menu.h"
#include "includes/RW/Loading.h"
#include "includes/RW/Settings.h"

int main()
{
	RW::Settings settings;
	//load settings
	settings.read();

	sf::RenderWindow window;
	//create a window with appropiate settings
	settings.setWindow(window);

	RW::Environment env;
	//load version number
	env.read();

	RW::Loading loading;
	//load textures and sounds
	loading.loadFiles(window, settings);

	//display version
	std::cout << "Version: " << env.getVersion() << std::endl;

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
		menu.Update(window);
		menu.Compose(window);

		window.display();
	}

	//save settings on exit
	settings.save();

	return 0;
}