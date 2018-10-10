#pragma once
#include "SFML/Graphics.hpp"
#include "MapReader.h"
#include "Paths.h"

namespace RW 
{
	class FileReader
	{
	private:
		static MapReader mapreader;

		static std::string filetype;
		static std::vector<std::string> supportedtypes;
	public:
		static void read(const std::string &path);

		//getters 
		static bool isMap() { return filetype == supportedtypes[0]; }
		static bool isUnit() { return filetype == supportedtypes[1]; }
		static bool isJson() { return filetype == supportedtypes[2]; }
		static std::string getFileType() { return filetype; }
	};
}