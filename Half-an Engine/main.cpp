#include "SFML\Graphics.hpp"
#include <nfd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	sf::RenderWindow window;
	window.create(sf::VideoMode(800, 600), "Half-an Engine");

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			//insert input handling in here

			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::Color(60, 60, 60, 255));

		//nfdchar_t *outPath = NULL;
		//nfdresult_t result = NFD_OpenDialog(NULL, NULL, &outPath);

		//if (result == NFD_OKAY) {
		//	puts("Success!");
		//	puts(outPath);
		//	free(outPath);
		//}
		//else if (result == NFD_CANCEL) {
		//	puts("User pressed cancel.");
		//}
		//else {
		//	printf("Error: %s\n", NFD_GetError());
		//}

		//insert drawing commands in here

		window.display();
	}

	return 0;
}