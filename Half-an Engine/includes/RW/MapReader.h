#pragma once
#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream>
#include "SFML\System.hpp" //for vectors

namespace RW
{
	class MapReader
	{
	private:
		//0-summer , 1-wastelands, 2 -winter
		static unsigned short theme; //contains the theme of the current map

		static unsigned short tiles[300][300]; //c ontains map tiles info
		static sf::Vector2i tilessize; //holds the size of the selected map (number of tiles x and y)

		static sf::Vector2i spawnpoints[12]; // contains the spots where players can spawn
		static unsigned short spawnsize; // holds the number of spwanpoints declared in a specific map 

		static sf::Vector2i goldmines[24]; // contains coordinates of different gold mines
		static unsigned short minesize; // holds the number of mines on the map

		static void clear(); //reads map number mapnr
	public:
		static void read(const std::string &file); //reads map number mapnr

		//getters
		static unsigned short getTheme() { return theme; }
		static unsigned short getTiles(const unsigned short &x, const unsigned short &y) { return tiles[x][y]; }
		static sf::Vector2i getTilessize() { return tilessize; }
		static sf::Vector2i getSpawnpoints(const unsigned short &i) { return spawnpoints[i]; }
		static unsigned short getSpawnsize() { return spawnsize; }
		static sf::Vector2i getGoldmines(const unsigned short &i) { return goldmines[i]; }
		static unsigned short getMinesize() { return minesize; }
	};
}