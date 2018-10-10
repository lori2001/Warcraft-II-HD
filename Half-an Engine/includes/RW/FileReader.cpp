#include "FileReader.h"

namespace RW
{
	MapReader FileReader::mapreader;
	std::string FileReader::filetype;
	std::vector<std::string> FileReader::supportedtypes = { "map", "unit", "json" }; //holds all supported filetypes

	void FileReader::read(const std::string &path)
	{
		std::size_t found = path.find_last_of(".");
		filetype = path.substr(found + 1);

		if (filetype == supportedtypes[0]) // map
		{
			mapreader.read(path);
		}
	}
}