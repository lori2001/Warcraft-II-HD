#include "FileReader.h"

namespace ngin {
	FileReader::INPUT_TYPE FileReader::cleanInput(std::string& input)
	{
		bool onlyspaces = true;

		size_t commentpos = input.find("//"); // these are the caracters that mean comment
		bool comment = false;

		// if comment found
		if (commentpos != std::string::npos) {
			input.erase(commentpos, input.length()); // erase comment
			comment = true;
		}

		// checks for potential empty lines and ignores them
		for (std::string::const_iterator i = input.begin(); i != input.end(); ++i)
		{
			if (onlyspaces && *i != ' ' && *i != '\t')
			{
				onlyspaces = false;
			}
		}

		if (input != " " && !onlyspaces) {
			return INPUT_TYPE::OK;
		}
		else if (!comment) {
			return INPUT_TYPE::CLEAR_FAIL;
		}
		else {
			return INPUT_TYPE::EMPTY;
		}
	}

	bool FileReader::findAndClear(std::string& input, const std::string& toFind)
	{
		auto finder = input.find(toFind); // search for toFind string

		if (finder != std::string::npos) { // if found
			input = input.replace(finder, toFind.size(), ""); // clear
			return true;
		}
		else return false;
	}
}
