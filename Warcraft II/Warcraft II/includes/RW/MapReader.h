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
		static std::string maps[20]; // contains the names of maps loaded in
		static unsigned int mapsnr; //contains the number of maps loaded in
		static unsigned int selectedmap; //contains the number of the currently selected map

		//0-summer , 1-wastelands, 2 -winter
		static unsigned int theme; //contains the theme of the current map

		static unsigned int tiles[300][300]; //c ontains map tiles info
		static sf::Vector2i tilessize; //holds the size of the selected map (number of tiles x and y)

		static sf::Vector2i spawnpoints[12]; // contains the spots where players can spawn
		static unsigned int spawnsize; // holds the number of spwanpoints declared in a specific map 

		static sf::Vector2i goldmines[24]; // contains coordinates of different gold mines
		static unsigned int minesize; // holds the number of mines on the map

		static void clear(); //reads map number mapnr
	public:
		static void readList(); //reads the list of map names
		static void read(); //reads map number mapnr

		//setters
		static void shiftSelectedmap(const int &shiftnr); //changes selectedmap by the amunt specified
		static void setSelectedmap(const unsigned int &newnr); //changes selectedmap to the number specified

		//getters
		static std::string getMaps(unsigned int i) { return maps[i]; }
		static unsigned int getMapsnr() { return mapsnr; }
		static unsigned int getSelectedmap() { return selectedmap; }
		static unsigned int getTheme() { return theme; }
		static unsigned int getTiles(const unsigned int &x, const unsigned int &y) { return tiles[x][y]; }
		static sf::Vector2i getTilessize() { return tilessize; }
		static sf::Vector2i getSpawnpoints(const unsigned int &i) { return spawnpoints[i]; }
		static unsigned int getSpawnsize() { return spawnsize; }
		static sf::Vector2i getGoldmines(const unsigned int &i) { return goldmines[i]; }
		static unsigned int getMinesize() { return minesize; }
	};
}