#include "Paths.h"

namespace RW {
	std::string Paths::gamePath;
	nfdchar_t* Paths::path = NULL;
	nfdresult_t Paths::dialog;

	bool Paths::chooseGamePath()
	{
		std::cout << "Please choose the location of the warcraft folder!" << std::endl;
		dialog = NFD_PickFolder(NULL, &path);

		if (dialog == NFD_OKAY) {
			gamePath = path;
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