#include "FileReader.h"

namespace RW
{
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