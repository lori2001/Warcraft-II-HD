#include "SettingsFile.h"
#include <fstream>

std::string SettingsFile::playerName_;

void SettingsFile::load()
{
	std::ifstream in("settings.json");

	if (!in) // if does not exist
		create(); // create a json file containing default settings
	else
		in >> json_; // read json file

	// set non-ngin variable(s)
	playerName_ = json_["Player_Name"].get<std::string>();

	// boundaries' check and correct
	if (json_["Sound_Volume"].get<float>() < 0 || json_["Sound_Volume"].get<float>() > 1)
	{
		json_["Sound_Volume"] = 0.5F;
		NG_LOG_WARN("settings.json -> Sound_Volume out of bounds -- corrected");
	}
	if (json_["Music_Volume"].get<float>() < 0 || json_["Music_Volume"].get<float>() > 1)
	{
		json_["Music_Volume"] = 0.5F;
		NG_LOG_WARN("settings.json -> Music_Volume out of bounds -- corrected");
	}
}

void SettingsFile::save()
{
	std::ofstream out("settings.json");

	std::string name = playerName_;

	// Filter empty name strings
	bool onlyspaces = true;
	for (std::string::const_iterator i = name.begin(); i != name.end(); ++i)
		onlyspaces = (*i == ' ');

	if (name == "" || onlyspaces)
		playerName_ = "[Enter Name]"; // if empty / reset to default

	json_["Player_Name"] = playerName_;

	out << json_.dump(4); // print out in an organised way
}

void SettingsFile::create()
{
	// get the maximum resolution the monitor supports
	sf::VideoMode maxres = sf::VideoMode::getDesktopMode();
	playerName_ = "[Enter Name]";

	// set keys to default settings
	json_["Player_Name"] = playerName_;
	json_["Video_Mode"]["Width"] = maxres.width;
	json_["Video_Mode"]["Height"] = maxres.height;
	json_["Video_Mode"]["BitsPerPixel"] = maxres.bitsPerPixel;
	json_["Window_Type"] = static_cast<int>(ngin::WINDOW_TYPE::WINDOW_FULLSCREEN);
	json_["Sound_Volume"] = 0.5F;
	json_["Music_Volume"] = 0.5F;

	// print out to file
	save();
}
