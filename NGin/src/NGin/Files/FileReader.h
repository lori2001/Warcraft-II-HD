#pragma once
#include <string>

namespace ngin {
	class FileReader {
	public:
		virtual void read() = 0;
		virtual void save() = 0;
	protected:
		enum class INPUT_TYPE {
			OK = 0,
			EMPTY,
			CLEAR_FAIL
		};

		// cleans input from comments (//)
		// and empty lines
		INPUT_TYPE cleanInput(std::string& input);

		// finds toFind in input and erases it
		// only returns false if not found
		bool findAndClear(std::string& input, const std::string& toFind);
	};
}