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

	if (toolbar.getWindowed())
	{
		sf::Event toolbarevent;

		while (toolbar.window.pollEvent(toolbarevent))
		{
			toolbar.handleInput(toolbarevent, mouse); //gets input

			if (toolbarevent.type == sf::Event::Resized)
			{
				toolbar.window.onResize(sf::Vector2i(toolbarevent.size.width, toolbarevent.size.height));
			}
			else if (toolbarevent.type == sf::Event::Closed || toolbar.B0getActive()) 
			{
				toolbar.B0setActive(false);
				toolbar.unwindowize(window.get1920Scale());
				toolbar.window.close();
			}
		}
	}

	while (window.pollEvent(event))
	{
		toolbar.handleInput(event, mouse); //gets input

		if (event.type == sf::Event::Resized)
		{
			sf::FloatRect visibleArea(0, 0, (float)event.size.width, (float)event.size.height);
			window.setView(sf::View(visibleArea));
			window.onResize(sf::Vector2i(event.size.width, event.size.height));

			if(!toolbar.getWindowed())
				toolbar.setTransform(window.get1920Scale());
		}
		else if (toolbar.B0getActive()) {
			toolbar.B0setActive(false);
			toolbar.window.create(sf::VideoMode(int(toolbar.getWindowSize().x * window.get1920Scale().x), int(toolbar.getWindowSize().y * window.get1920Scale().y)), "Toolbar");
			toolbar.windowize(window.get1920Scale());
		}
		else if (event.type == sf::Event::Closed)
			window.close();
	}
}

void Program::Update(Window &window)
{
	for (int i = 0; i < 5; i++)
	{
		if (i < 5 && toolbar.D0getActive(i))
		{
			toolbar.D0setActive(i, false);

			if (i == 1) {
				paths.chooseFilePath();
			}
		}
	}
}

void Program::Compose(Window &window)
{
	if (toolbar.getWindowed())
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
