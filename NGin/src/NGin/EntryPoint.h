#pragma once
#include "Levels/MainLevel.h"

// only add once to the program
#ifdef MAIN_LEVEL
extern ngin::MainLevel* setMainLevel();

int main()
{
	auto app = setMainLevel();
	app->run();
	delete app;

	return 0;
}
#endif