#pragma once
#include "SFML/Graphics.hpp"
#include "MapReader.h"
#include "Paths.h"

namespace RW 
{
	class FileReader
	{
	private:
		MapReader mapreader;

		std::string filetype;
		std::vector<std::string> supportedtypes = { "map", "unit", "json"}; //holds all supported filetypes
	public:
		void read(const std::string &path);

		//getters 
		bool isMap() const { return filetype == supportedtypes[0]; }
		bool isUnit() const { return filetype == supportedtypes[1]; }
		bool isJson() const { return filetype == supportedtypes[2]; }
		std::string getFileType() { return filetype; }
	};
}