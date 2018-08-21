#include "MapReader.h"

namespace RW
{
	std::string MapReader::maps[20];
	unsigned short MapReader::mapsnr = 0;
	unsigned short MapReader::selectedmap = 0;

	//0-summer , 1-wastelands, 2 -winter
	unsigned short MapReader::theme = 0;

	unsigned short MapReader::tiles[300][300];
	sf::Vector2i MapReader::tilessize{ 0, 0 };

	sf::Vector2i MapReader::spawnpoints[12];
	unsigned short MapReader::spawnsize = 0;

	sf::Vector2i MapReader::goldmines[24];
	unsigned short MapReader::minesize = 0;

	void MapReader::clear()
	{
		//theme = 0;

		//for (int y = 0; y < 300; y++)
		//	for (int x = 0; x < 300; x++)
		//		tiles[x][y] = { 0 };

		//tilessize = { 0, 0 };

		//for (int i = 0; i < 12; i++)
		//	spawnpoints[i] = { 0,0 };

		//spawnsize = 0;

		//for (int i = 0; i < 24; i++)
		//	goldmines[i] = { 0,0 };

		//minesize = 0;
	}
	void MapReader::readList()
	{
		std::ifstream in("assets/maps/list.txt");
		std::string input;

		if (!in) //if reading fails
		{
			std::cout << "ERROR: assets/maps/list.txt does not exist.";
			assert(false);
		}
		else while (std::getline(in, input))
		{
			maps[mapsnr] = input;
			mapsnr++;
		}
	}
	void MapReader::read(const unsigned short &mapnr)
	{
		std::ifstream in("assets/maps/" + maps[mapnr]); //opens the map specified

		clear(); // clears tiles' data

		selectedmap = mapnr; // the selected map is the map specified to get loaded
		bool themewasset = false; // true if theme was specified in file, false if not

		std::string input; //reads input by each word

		if (!in) // if file cannot load
		{
			std::cout << "ERROR: " + maps[mapnr] +  " file specified in list.txt does not exist."; //output the exact error circumstances
			assert(false); //stop program and signal an error
		}
		else while (in >> input)
		{
			if (input == "Theme:")
			{
				in >> input;

				themewasset = true;

				if (input == "Summer" || input == "summer")
					theme = 0;
				else if (input == "Wastelands" || input == "wastelands")
					theme = 1;
				else if (input == "Winter" || input == "winter")
					theme = 2;
			}
			else if (input == "<tiles>")
			{
				while (std::getline(in, input) && input != "</tiles>")
				{
					bool onlyspaces = true;

					for (std::string::const_iterator i = input.begin(); i != input.end(); ++i)
					{
						if (*i != ' ' && *i != '\t')
						{
							onlyspaces = false;
							break;
						}
					}

					if (input != " " && !onlyspaces) // checks for potential empty lines
					{
						tilessize.x = 0;

						std::istringstream iss(input);

						while (iss >> tiles[tilessize.x][tilessize.y])
						{
							tilessize.x++;
						}
						tilessize.y++;
					}
				}
			}
			else if (input == "<spawnpoint>")
			{
				in >> spawnpoints[spawnsize].x;
				in >> input;
				in >> spawnpoints[spawnsize].y;
				spawnsize++;
			}
			else if (input == "<goldmine>")
			{
				in >> goldmines[minesize].x;
				in >> input;
				in >> goldmines[minesize].y;
				minesize++;
			}
		}

		if(!themewasset)
		{
			std::cout << "WARNING: Theme is NOT specified inside " + maps[mapnr] << std::endl;
			std::cout << "Theme will default to Summer" << std::endl;
		}

		//each maps should have at least 2 spawnpoints and 1 gold mine
		//assert(spawnsize >= 2);
		//assert(minesize >= 1);
	}
}