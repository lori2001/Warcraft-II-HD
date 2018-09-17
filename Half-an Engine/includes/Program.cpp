#include "Program.h"

void Program::Setup(Window &window)
{
	toolbar.setTransform(window.get1920Scale());
}

void Program::handleInput(Window &window)
{
	if(window.hasFocus())
		mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window)); //gets mouse position relative to window
	else if(toolbar.window.hasFocus())
		mouse = toolbar.window.mapPixelToCoords(sf::Mouse::getPosition(toolbar.window)); //gets mouse position relative to window

	sf::Event event;

	if (toolbar.isWindowed)
	{
		sf::Event toolbarevent;

		while (toolbar.window.pollEvent(toolbarevent))
		{
			toolbar.handleInput(toolbarevent, mouse);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				std::cout << (float)window.getRes().x / (float)toolbar.window.getRes().x << " " << (float)window.getRes().y / (float)toolbar.window.getRes().y;
				std::cout << window.get1920Scale().x << "  " << window.get1920Scale().y << std::endl;
			}
			else if (toolbarevent.type == sf::Event::Resized)
			{
				toolbar.window.onResize(sf::Vector2i(toolbarevent.size.width, toolbarevent.size.height));

				std::cout << (float)toolbar.window.getRes().x / (float)window.getRes().x * window.get1920Scale().x << " ";
				std::cout << (float)toolbar.window.getRes().y / (float)window.getRes().y * window.get1920Scale().y << std::endl;

			}
			else if (toolbarevent.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				toolbar.isWindowed = false;
				toolbar.window.close();
			}
		}
	}

	while (window.pollEvent(event))
	{
		toolbar.handleInput(event, mouse);

		if (event.type == sf::Event::Resized)
		{
			sf::FloatRect visibleArea(0, 0, (float)event.size.width, (float)event.size.height);
			window.setView(sf::View(visibleArea));
			window.onResize(sf::Vector2i(event.size.width, event.size.height));
			toolbar.setTransform(window.get1920Scale());
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			toolbar.isWindowed = true;
			toolbar.window.create(sf::VideoMode(int(toolbar.getSize().x * window.get1920Scale().x), int(toolbar.getSize().y * window.get1920Scale().y)), "Toolbar");
		}
		else if (event.type == sf::Event::Closed)
			window.close();
	}
}

void Program::Update(Window &window)
{
}

void Program::Compose(Window &window)
{
	if (toolbar.isWindowed)
	{
		toolbar.window.clear(sf::Color::Color(60, 60, 60, 255));
		toolbar.window.draw(toolbar);
		toolbar.window.display();
	}
	else
	{
		window.draw(toolbar);
	}
}
