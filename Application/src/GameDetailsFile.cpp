#include "GameDetailsFile.h"
#include <fstream>
#include <stdlib.h> // random
#include <time.h> // random

ng::json GameDetailsFile::json_;
std::vector<int> GameDetailsFile::actualRacesIndex_;
bool GameDetailsFile::isLoaded_ = false;

void GameDetailsFile::load(const char* fileName)
{
	if (!isLoaded_) {
		std::ifstream in(fileName);

		if (!in) // if does not exist
		{
			create(); // create a json file containing default settings
			save(fileName);
			NG_LOG_WARN("Savefile not loaded, created and saved instead.");
		}
		else
			in >> json_; // read json file

		isLoaded_ = true;
	}
}

void GameDetailsFile::save(const char* fileName)
{
	if (isLoaded_)
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
	else {
		NG_LOG_WARN(fileName, " save called but not ever loaded! " );
	}
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

void GameDetailsFile::setNPCDifficulty(const unsigned npcIndex, const std::string& difficulty)
{
	if (npcIndex >= maxNumberOfNPCs) throw std::out_of_range("index received is out of range");
	json_[NPCsKey][std::to_string(npcIndex)][difficultyKey] = difficulty;
}

void GameDetailsFile::setNPCRace(const unsigned npcIndex, const std::string& race)
{
	if (npcIndex >= maxNumberOfNPCs) throw std::out_of_range("index received is out of range");
	json_[NPCsKey][std::to_string(npcIndex)][raceKey] = race;
}

void GameDetailsFile::setNPCTeam(const unsigned npcIndex, const std::string& team)
{
	if (npcIndex >= maxNumberOfNPCs) throw std::out_of_range("index received is out of range");
	json_[NPCsKey][std::to_string(npcIndex)][teamKey] = team;
}

void GameDetailsFile::setNPCColor(const unsigned npcIndex, const unsigned color)
{
	if (npcIndex >= maxNumberOfNPCs) throw std::out_of_range("index received is out of range");
	json_[NPCsKey][std::to_string(npcIndex)][colorKey] = color;
}

void GameDetailsFile::setTeamRelativeColors(const bool isRelative)
{
	json_[teamRelativeColorsKey] = isRelative;
}

void GameDetailsFile::setMapIndex(const unsigned mapIndex)
{
	json_[mapIndexKey] = mapIndex;
}

void GameDetailsFile::setPlayerGold(const int value)
{
	json_[resources][gold] = value;
}

void GameDetailsFile::setPlayerWood(const int value)
{
	json_[resources][wood] = value;
}

void GameDetailsFile::setPlayerOil(const int value)
{
	json_[resources][oil] = value;
}

void GameDetailsFile::setNPCGold(const unsigned npcIndex, int value)
{
	if (npcIndex >= maxNumberOfNPCs) throw std::out_of_range("index received is out of range");
	json_[NPCsKey][std::to_string(npcIndex)][resources][gold] = value;
}

void GameDetailsFile::setNPCWood(const unsigned npcIndex, int value)
{
	if (npcIndex >= maxNumberOfNPCs) throw std::out_of_range("index received is out of range");
	json_[NPCsKey][std::to_string(npcIndex)][resources][wood] = value;
}

void GameDetailsFile::setNPCOil(const unsigned npcIndex, int value)
{
	if (npcIndex >= maxNumberOfNPCs) throw std::out_of_range("index received is out of range");
	json_[NPCsKey][std::to_string(npcIndex)][resources][oil] = value;
}

void GameDetailsFile::create()
{
	// set keys to default settings
	setPlayerName("[Enter Name]");
	setPlayerRace(races_[0].string);
	setPlayerTeam(teams_[0]);
	setPlayerColor(colors_[0].toInteger());
	setPlayerGold(0);
	setPlayerWood(0);
	setPlayerOil(0);

	setNumberOfNPCs(1);
	setTeamRelativeColors(false);
	setMapIndex(0);

	for (int i = 0; i < maxNumberOfNPCs; i++) {
		setNPCRace(i, races_[0].string);
		setNPCDifficulty(i, difficulties_[0]);
		setNPCTeam(i, teams_[1 + i]);
		setNPCColor(i, colors_[1 + i].toInteger());
		setNPCGold(i, 0);
		setNPCWood(i, 0);
		setNPCOil(i, 0);
	}

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
