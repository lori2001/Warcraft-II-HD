#pragma once
#include "NGin.h"
#include <stdexcept>

class GameDetailsFile {
public:
	// this is where random races are seeded
	static void load();

	static void save();

	static std::string getPlayerName()  { return json_[playerKey][playerNameKey].get<std::string>(); }
	static std::string getPlayerRace()  { return json_[playerKey][raceKey].get<std::string>(); }
	static std::string getPlayerTeam()  { return json_[playerKey][teamKey].get<std::string>(); }
	static unsigned getPlayerColor() { return json_[playerKey][colorKey].get<unsigned>(); }

	static unsigned getNumberOfNPCs() { return json_[numberOfNPCsKey].get<unsigned>(); }

	static std::string getNPCDifficulty(const unsigned npcIndex) {
		if (npcIndex >= maxNumberOfNPCs) throw std::out_of_range("index received is out of range");
		return json_[NPCsKey][std::to_string(npcIndex)][difficultyKey].get<std::string>();
	}
	// includes random race
	static std::string getNPCRace(const unsigned npcIndex) {
		if (npcIndex >= maxNumberOfNPCs) throw std::out_of_range("index received is out of range");
		return json_[NPCsKey][std::to_string(npcIndex)][raceKey].get<std::string>();
	}
	static std::string getNPCTeam(const unsigned npcIndex) {
		if (npcIndex >= maxNumberOfNPCs) throw std::out_of_range("index received is out of range");
		return json_[NPCsKey][std::to_string(npcIndex)][teamKey].get<std::string>();
	}
	static unsigned getNPCColor(const unsigned npcIndex) {
		if (npcIndex >= maxNumberOfNPCs) throw std::out_of_range("index received is out of range");
		return json_[NPCsKey][std::to_string(npcIndex)][colorKey].get<unsigned>();
	}
	static bool getTeamRelativeColors() {
		return json_[teamRelativeColorsKey].get<bool>();
	}
	static unsigned getMapIndex() {
		return json_[mapIndexKey].get<unsigned>();
	}

	// retrieves actual race string (without random)
	static std::string getActualPlayerRace();
	static std::string getActualNPCRace(const unsigned npcIndex);

	static constexpr const unsigned maxNumberOfNPCs = 11;

protected:
	static void setPlayerName(const std::string& playerName) { json_[playerKey][playerNameKey] = playerName; }
	static void setPlayerRace(const std::string& race) { json_[playerKey][raceKey] = race; }
	static void setPlayerTeam(const std::string& team) { json_[playerKey][teamKey] = team; }
	// TODO: checks for the rest of colors too,
	// if already set it pics the next color in vector
	// returns true if set to specified value
	static void setPlayerColor(const unsigned colorInt) { json_[playerKey][colorKey] = colorInt; }
	
	static void setNumberOfNPCs(const unsigned numOfNPCs) {
		// should not be set bigger than size of colors and teams vectors(11)
		if (numOfNPCs >= colors_.size()) throw std::out_of_range("not enough colors for each defined npc");
		json_[numberOfNPCsKey] = numOfNPCs;
	}

	// wrong npc index throws exception
	static void setNPCDifficulty(const unsigned npcIndex, const std::string& difficulty) {
		if (npcIndex >= maxNumberOfNPCs) throw std::out_of_range("index received is out of range");
		json_[NPCsKey][std::to_string(npcIndex)][difficultyKey] = difficulty;
	}
	static void setNPCRace(const unsigned npcIndex, const std::string& race) {
		if (npcIndex >= maxNumberOfNPCs) throw std::out_of_range("index received is out of range");
		json_[NPCsKey][std::to_string(npcIndex)][raceKey] = race;
	}
	static void setNPCTeam(const unsigned npcIndex, const std::string& team) {
		if (npcIndex >= maxNumberOfNPCs) throw std::out_of_range("index received is out of range");
		json_[NPCsKey][std::to_string(npcIndex)][teamKey] = team;
	}
	static void setNPCColor(const unsigned npcIndex, const unsigned color) {
		if (npcIndex >= maxNumberOfNPCs) throw std::out_of_range("index received is out of range");
		json_[NPCsKey][std::to_string(npcIndex)][colorKey] = color;
	}
	static void setTeamRelativeColors(const bool isRelative) {
		json_[teamRelativeColorsKey] = isRelative;
	}
	static void setMapIndex(const unsigned mapIndex) {
		json_[mapIndexKey] = mapIndex;
	}

	// --- Selectables' content --------------------
	struct ColoredString {
		sf::String string;
		sf::Color color;
	};
	inline static const std::array<ColoredString, 3> races_
	{{{ "Random" , sf::Color::Yellow }, // DO NOT CHANGE POSITION
	  { "Orcs[" , sf::Color::Red },
	  { "Humans]" , sf::Color::Blue }}};

	inline static const std::array<std::string, 3> difficulties_
	{ "Easy", "Medium", "Hard" };

	inline static const std::array<std::string, maxNumberOfNPCs + 1> teams_
	{ "Team 1",  "Team 2",  "Team 3", //        +1 for the player ^ 
	  "Team 4",  "Team 5",  "Team 6",
	  "Team 7",  "Team 8",  "Team 9",
	  "Team 10", "Team 11", "Team 12", };

	inline static const std::array<sf::Color, maxNumberOfNPCs + 1> colors_
	{   sf::Color(255,   0,   0), // 1.red    +1 for the player ^
		sf::Color(0, 255,   0), // 2.green
		sf::Color(0,   0, 255), // 3.blue
		sf::Color(255,  69,   0), // 4.orange
		sf::Color(255, 255,   0), // 5.yellow
		sf::Color(0, 255, 255), // 6.cyan
		sf::Color(128,   0, 128), // 7.purple
		sf::Color(255, 255, 255), // 8.white
		sf::Color(139,  69,  19), // 9.brown
		sf::Color(128, 128, 128), // 10.grey
		sf::Color(255,  20, 147), // 11.pink
		sf::Color(0,   0,   0)  // 12.black
	};

private:
	static constexpr const char* fileName = "game_details.json";

	// saves random race choices
	static std::vector<int> actualRacesIndex_;

	static ng::json json_;

#define KEY static constexpr const char*
	KEY teamRelativeColorsKey = "teamRelativeColors";
	KEY playerKey = "player";
	KEY	playerNameKey = "playerName";
	KEY numberOfNPCsKey = "numberOfNPCs";
	KEY NPCsKey = "NPCs";
	KEY raceKey = "race";
	KEY difficultyKey = "difficulty";
	KEY teamKey = "team";
	KEY colorKey = "color";
	KEY mapIndexKey = "mapIndex";
#undef KEY

	static void create(); // gets called if loading fails
};