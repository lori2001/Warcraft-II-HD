#include "SFML\Graphics.hpp"
#include "includes/RW/Environment.h"
#include "includes/Menu.h"
#include "includes/RW/Loading.h"

int main()
{
	sf::RenderWindow window;
	window.create(sf::VideoMode(800, 600), "Warcraft II");

	RW::Environment env;
	env.read();

	RW::Loading loading;
	loading.loadFiles(window);

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

	return 0;
}