#pragma once
#include <vector>
#include "SFML\Graphics.hpp"

struct Players
{
public: // not needed but put for safety

	//contains player's info
	static std::string playername;
	static unsigned short playerrace;
	static unsigned short playerteam;
	static unsigned short playercolor;

	//contains ai's info
	static unsigned short ais; // contains the number of active ai's
	static unsigned short ailimit; // max value 11
	static unsigned short aidifficulty[11]; //difficulty for each ai
	static unsigned short airace[11];  //race for each ai
	static unsigned short aiteam[11]; //team for each ai
	static unsigned short aicolor[11]; //color for each ai

	static bool relativecolors; // if active colors are set realtive to teams

	static bool canStart(); // checks if the name is not empty and if there is at least 2 teams (if not returns false)

	static void setAiColorTeamRelative(); // sets colors relative to their teams
	//used to set a single ai's color (returns false if it fails)
	static bool setAiColor(const unsigned short &i, const unsigned short &value); //sets ai color avoiding same-color outputs
	//used when the number of ai's changes
	static void setAiColorsAfter(const unsigned short & from);
	static bool setPlayerColor(const unsigned short &value); //sets player color avoiding same-color outputs (returns false if it fails)
	static void resetColors(); //set every color to default
	static void resetValues(); //set every value to default
};
