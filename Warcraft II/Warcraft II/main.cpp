#include "SFML\Graphics.hpp"
#include "includes/RW/Settings.h"
#include "includes/RW/Loading.h"
#include "includes/RW/Environment.h"
#include "includes/Menu.h"

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

	Menu menu;
	menu.Setup(window);

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			menu.handleInput(window, event);

			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		//contains frame-by-frame logic
		menu.Update(window);
		//contains drawing commands
		menu.Compose(window);

		window.display();
	}

	//save settings on exit
	settings.save();

	return 0;
}