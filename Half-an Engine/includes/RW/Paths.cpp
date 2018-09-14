#include "Paths.h"

namespace RW {
	std::string Paths::gamePath;
	nfdchar_t* Paths::path = NULL;
	nfdresult_t Paths::dialog;

	bool Paths::chooseGamePath()
	{
		std::cout << "Please choose the location of the warcraft's exe file!" << std::endl;
		dialog = NFD_OpenDialog(NULL, NULL, &path);;

		if (dialog == NFD_OKAY) {
			gamePath = path;
			std::size_t found = gamePath.find_last_of("/\\");
			std::string temp = path;
			gamePath = temp.substr(0, found);
			//std::cout << " path: " << gamePath.substr(0, found) << '\n';
			//std::cout << " file: " << gamePath.substr(found + 1) << '\n';
			free(path);

		}
		else if (dialog == NFD_CANCEL) {
			return 0;
		}
		else {
			std::cout << "Error: " << NFD_GetError() << std::endl;
		}

		return 1;
	}
}