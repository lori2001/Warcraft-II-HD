#pragma once
#include "Levels/Main.h"

// only add once to the program
#ifdef MAIN_LEVEL
extern ng::Main* setMainLevel();

int main()
{
	auto app = setMainLevel();
	app->run();
	delete app;

	return 0;
}
#endif