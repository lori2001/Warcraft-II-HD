#pragma once
#include <iostream>
#include <fstream>
#include "../../libs/json/json.hpp"

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
		std::string getVersion() const {
			return  std::to_string(jsonfile["version"]["major"].get<int>()) + "." +
					std::to_string(jsonfile["version"]["minor"].get<int>()) + "." +
					std::to_string(jsonfile["version"]["build"].get<int>());
		}

		// Write -1 to not modify one specific parameter
		void setVersion(int major, int minor, int build);
	};
}