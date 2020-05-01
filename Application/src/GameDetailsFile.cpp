#include "GameDetailsFile.h"
#include <fstream>
#include <stdlib.h> // random
#include <time.h> // random

ng::json GameDetailsFile::json_;
std::vector<int> GameDetailsFile::actualRacesIndex_;

void GameDetailsFile::load()
{
	std::ifstream in(fileName);

	if (!in) // if does not exist
		create(); // create a json file containing default settings
	else
		in >> json_; // read json file

	// intialize random seed for random races
	srand(static_cast<unsigned>(time(NULL)));

	actualRacesIndex_.clear();

	// player race in case of random
	actualRacesIndex_.push_back(1 + rand() % (races_.size() - 1));
	//                          ^ any index except the first  ^
	for (int i = 1; i <= maxNumberOfNPCs; i++) {
		actualRacesIndex_.push_back(1 + rand() % (races_.size() - 1));
	}
}

void GameDetailsFile::save()
{
	std::ofstream out(fileName);

	// Filter empty name strings
	std::string name = json_[playerKey][playerNameKey];
	bool onlyspaces = true;
	for (std::string::const_iterator i = name.begin(); i != name.end(); ++i)
		onlyspaces = (*i == ' ');
	if (name == "" || onlyspaces)  // if empty or only spaces -> reset to default
		name = "[Enter Name]";

	json_[playerKey][playerNameKey] = name;

	out << json_.dump(4); // print out in an organised way
}

std::string GameDetailsFile::getActualPlayerRace()
{
	std::string actualRace = getPlayerRace();

	// if is random
	if (actualRace == races_[0].string)
		actualRace = races_[actualRacesIndex_[0]].string; // index 0 is player!

	return actualRace;
}

std::string GameDetailsFile::getActualNPCRace(const unsigned npcIndex)
{
	std::string actualRace = getNPCRace(npcIndex);

	// if is random
	if (actualRace == races_[0].string)
		actualRace = races_[actualRacesIndex_[npcIndex + 1]].string; // add one because of player!

	return actualRace;
}

void GameDetailsFile::create()
{
	// set keys to default settings
	setPlayerName("[Enter Name]");
	setPlayerRace(races_[0].string);
	setPlayerTeam(teams_[0]);
	setPlayerColor(colors_[0].toInteger());

	setNumberOfNPCs(1);
	setTeamRelativeColors(false);
	setMapIndex(0);

	for (int i = 0; i < maxNumberOfNPCs; i++) {
		setNPCRace(i, races_[0].string);
		setNPCDifficulty(i, difficulties_[0]);
		setNPCTeam(i, teams_[1 + i]);
		setNPCColor(i, colors_[1 + i].toInteger());
	}

	// print out to file
	save();
}
