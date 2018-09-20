#pragma once
#include <iostream>
#include <nfd.h>
#include <string>

namespace RW {
	class Paths {
	private:
		static std::string gamePath;
		static std::string filePath;
		static nfdchar_t *path;
		static nfdresult_t dialog;
	public:
		static bool chooseGamePath();
		static bool chooseFilePath();

		//getters
		static std::string getGamePath() { return gamePath; }
	};
}