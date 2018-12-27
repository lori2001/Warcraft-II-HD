#include <iostream>
#include "Settings.h"

namespace RW
{
	io::json Settings::jsonfile;

	sf::Vector2i Settings::oldres;
	bool Settings::oldfullscreen = false;

	void Settings::create()
	{
		//get the maximum resolution the monitor supports
		sf::VideoMode maxres = sf::VideoMode::getDesktopMode();

		//set keys to default settings
		jsonfile["playerName"] = "[Enter Name]";
		jsonfile["resolution"]["width"] = maxres.width;
		jsonfile["resolution"]["height"] = maxres.height;
		jsonfile["fullscreen"] = true;
		jsonfile["soundfx"] = 5;
		jsonfile["music"] = 5;

		//print out
		save();
	}
	void Settings::applyToWindow(sf::RenderWindow & window)
	{
		if (jsonfile["fullscreen"].get<bool>())
			window.create(sf::VideoMode(jsonfile["resolution"]["width"], jsonfile["resolution"]["height"]), "Warcraft II", sf::Style::Fullscreen);
		else
			window.create(sf::VideoMode(jsonfile["resolution"]["width"], jsonfile["resolution"]["height"]), "Warcraft II", sf::Style::Titlebar | sf::Style::Close);

		sf::View view(sf::FloatRect(0, 0, 1920, 1080));
		window.setView(view);

		window.setMouseCursorVisible(false);
	}

	void Settings::read()
	{
		std::ifstream in("settings.json");

		if (!in)
			create(); //create a json file containing default settings
		else
			in >> jsonfile; //read json file

		//update old-values thus avoiding conflicts
		oldres = sf::Vector2i(jsonfile["resolution"]["width"].get<int>(), jsonfile["resolution"]["height"].get<int>());
		oldfullscreen = jsonfile["fullscreen"].get<bool>();

		//check if music is in range
		assert(0 <= jsonfile["music"].get<unsigned int>() && jsonfile["music"].get<unsigned int>() <= 10);
		assert(0 <= jsonfile["soundfx"].get<unsigned int>() && jsonfile["soundfx"].get<unsigned int>() <= 10);
	}

	void Settings::save()
	{
		std::ofstream out("settings.json");

		std::string name = jsonfile["playerName"].get<std::string>();
		bool onlyspaces = true;

		for (std::string::const_iterator i = name.begin(); i != name.end(); ++i)
			onlyspaces = (*i == ' ');

		if (name == "" || onlyspaces)
			jsonfile["playerName"] = "[Enter Name]";

		out << jsonfile.dump(4);
	}
}