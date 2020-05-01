#include "SettingsFile.h"
#include <fstream>

ng::json SettingsFile::json_;

void SettingsFile::load()
{
	std::ifstream in(fileName);

	if (!in) // if does not exist
		create(); // create a json file containing default settings
	else
		in >> json_; // read json file

	// boundaries' check and correct
	if (json_[soundVolumeKey].get<float>() < 0 || json_[soundVolumeKey].get<float>() > 1)
	{
		json_[soundVolumeKey] = 0.5F;
		NG_LOG_WARN(fileName, " -> ", soundVolumeKey ," out of bounds -- corrected");
	}
	if (json_[musicVolumeKey].get<float>() < 0 || json_[musicVolumeKey].get<float>() > 1)
	{
		json_[musicVolumeKey] = 0.5F;
		NG_LOG_WARN(fileName, " -> ", musicVolumeKey ," out of bounds -- corrected");
	}
}

void SettingsFile::save()
{
	std::ofstream out(fileName);

	out << json_.dump(4); // print out in an organised way
}

void SettingsFile::create()
{
	// get the maximum resolution the monitor supports
	sf::VideoMode maxres = sf::VideoMode::getDesktopMode();

	// set keys to default settings
	json_[videoModeKey][widthKey] = maxres.width;
	json_[videoModeKey][heightKey] = maxres.height;
	json_[videoModeKey][bitsPerPixelKey] = maxres.bitsPerPixel;
	json_[windowTypeKey] = static_cast<int>(ng::WINDOW_TYPE::WINDOW_FULLSCREEN);
	json_[soundVolumeKey] = 0.5F;
	json_[musicVolumeKey] = 0.5F;

	// print out to file
	save();
}
