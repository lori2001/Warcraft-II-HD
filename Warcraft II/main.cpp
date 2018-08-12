#include "SFML\Graphics.hpp"

int main()
{
	sf::RenderWindow window;
	window.create(sf::VideoMode(800, 600), "Warcraft II");

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			//insert input handling in here

			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		//insert drawing commands in here

		window.display();
	}

	return 0;
}