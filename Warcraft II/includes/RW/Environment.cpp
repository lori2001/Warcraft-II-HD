#include "Environment.h"

namespace RW
{
	void Environment::create()
	{
		jsonfile["version"]["major"] = 0;
		jsonfile["version"]["minor"] = 5;
		jsonfile["version"]["build"] = 1;

		// saves the file created
		save();
	}
	void Environment::save()
	{
		std::ofstream out("environment.json");

		if(!out)
			std::cout << "Failed to save environment.json The system may malfunction!" << std::endl;

		out << jsonfile.dump(4) << std::endl;
		out << "//This file contains the current version of the program" << std::endl;
		out << "//DO NOT change unless you have a really good reason";
	}
	void Environment::read()
	{
		std::ifstream in("environment.json");

		if(!in)
			std::cout << "environment.json file not found and has to be created. The displayed version may be incorrect." << std::endl;

		if (!in)
		{
			// if file doesn't exist create one
			// NOTE: it resets versions
			create();
		}
		else
		{
			//read from file
			in >> jsonfile;

			// +1  to build number
			int temp = jsonfile["version"]["build"];
			temp++;
			jsonfile["version"]["build"] = temp;

			//saves changes
			save();
		}
	}
	void Environment::setVersion(int major, int minor, int build)
	{
		if(major != -1)
			jsonfile["version"]["major"] = major;
		if(minor != -1)
			jsonfile["version"]["minor"] = minor;
		if(build != -1)
			jsonfile["version"]["build"] = build;
	}
}
