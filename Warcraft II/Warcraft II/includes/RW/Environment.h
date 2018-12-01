#pragma once
#include <iostream>
#include <fstream>
#include "../../vendor/json-develop/nlohmann/json.hpp"

namespace RW
{
	class Environment
	{
	private:
		io::json jsonfile;

		void create();
		void save();
	public:
		void read();

		//get version number as a string: "major.minor.build"
		std::string getVersion() const {
			return  std::to_string(jsonfile["version"]["major"].get<int>()) + "." +
					std::to_string(jsonfile["version"]["minor"].get<int>()) + "." +
					std::to_string(jsonfile["version"]["build"].get<int>());
		}

		//Write -1 to not modify one specific parameter
		void setVersion(int major, int minor, int build);
	};
}