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

			if (i == 1) // if New is pressed
			{
				paths.saveFilePath(); //open dialog for file location specification
				std::cout << paths.getFilePath() << std::endl;
			}
			else if (i == 2) // if Open is pressed
			{
				paths.openFilePath(); //open dialog for file opening
				filereader.read(paths.getFilePath()); // decides what type the file is and reads it in

				std::cout << "isMap: " << filereader.isMap() << std::endl;
				std::cout << "isUnit: " << filereader.isUnit() << std::endl;
				std::cout << "isJson: " << filereader.isJson() << std::endl;
				std::cout << std::endl << std::endl << std::endl;

				if (filereader.isMap()) {
					RW::MapReader mapreader;

					for (int y = 0; y < mapreader.getTilessize().y; y++) {
						for (int x = 0; x < mapreader.getTilessize().x; x++) {
							std::cout << mapreader.getTiles(x, y) << " ";
						}
						std::cout << std::endl;
					}
				}
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
