#include "MapFile.h"
#include <iostream>
#include <filesystem>

bool MapFile::scanDir()
{
	// Securely clean up possible previous paths
	paths_.clear();

	char buffer[MAX_PATH];
	// get .exe file path in buffer
	GetModuleFileName(NULL, buffer, sizeof(buffer));
	// mark the buffer at position before executable file name 
	// ex. C:\\example\\application.exe
	//                 ^ pos
	std::string::size_type pos = std::string(buffer).find_last_of("\\/");

	// generate absolute folder path from relative
	folderPath_ = std::string(buffer).substr(0, pos) + std::string(RELATIVE_FOLDER_PATH);

	try {
		// add all valid paths to their vector
		for (const auto& entry : std::filesystem::directory_iterator(folderPath_))
		{
			const std::string filePath = entry.path().u8string();

			// only load files with the right extension
			std::size_t found = filePath.find_last_of(".");
			if (filePath.substr(found + 1) == MAP_FILE_EXTENSION)
				paths_.push_back(filePath); // add path to vec
		}
	}
	catch (...)
	{
		NG_LOG_WARN(folderPath_);
		NG_LOG_WARN("Directory not found! Empty directory created. This might cause unexpected behaviour!");
		
		CreateDirectory(folderPath_.c_str(), NULL);
		
		return false;
	}
	
	return paths_.size() != 0; // if no maps found return false else retrun true
}

void MapFile::load(const std::string& path)
{
	std::ifstream in(path);

	if (in.is_open()) {
		std::string input;

		// clear up
		tiles_.clear();
		tileSize_ = { 0.0F, 0.0F };
		themeLocation_ = "";
		title_ = "";

		while (std::getline(in, input)) {

			// clears white lines and comments
			auto inputType = cleanInput(input);

			if (inputType == ng::FileReader::INPUT_TYPE::OK)
			{
				// --- Map Name -----------------------------------
				if (findAndClear(input, "Title: "))
					title_ = input;
				// ------------------------------------------------

				// --- Size of one tile ---------------------------
				if (findAndClear(input, "TileWidth:"))
					tileSize_.x = std::stof(input);
				if (findAndClear(input, "TileHeight:"))
					tileSize_.y = std::stof(input);
				// ------------------------------------------------

				// --- Theme --------------------------------------
				if (findAndClear(input, "Theme: ")) {
					if (input.find("Summer") != std::string::npos)
						themeLocation_ = "images/tiles/summer.png";
					else if (input.find("Wastelands") != std::string::npos)
						themeLocation_ = "images/tiles/wastelands.png";
					else if (input.find("Winter") != std::string::npos)
						themeLocation_ = "images/tiles/winter.png";
				}
				// ------------------------------------------------

				// --- Tiles --------------------------------------
				if (findAndClear(input, "<tiles>")) {
					bool goOn = true;
					do {
						goOn = !findAndClear(input, "</tiles>");
						inputType = cleanInput(input);

						if (inputType == ng::FileReader::INPUT_TYPE::OK)
						{
							std::istringstream iss(input);
							std::vector<unsigned> temp;

							// upload input string stream to temp
							int aux;
							while (iss >> aux) temp.push_back(aux);

							// upload temp as row of tiles
							tiles_.push_back(temp);
						}

						std::getline(in, input);

					} while (goOn);
				}
				// ------------------------------------------------
			}
		}
	}
	else {
		NG_LOG_ERROR("Unable To open file: ", path);
	}

	if (tiles_.size() <= 0) {
		NG_LOG_ERROR("No tiles specified in faulty mapfile:", path);
	}

	in.close();
}

void MapFile::save()
{
	// should trim down unnecessary 0-s
}

int MapFile::getMaxNumOfColumns()
{
	unsigned maxSize = 0;

	for (int i = 0; i < int(tiles_.size()); i++) {
		if (maxSize < tiles_[i].size()) {
			maxSize = tiles_[i].size();
		}
	}

	return static_cast<int>(maxSize);
}

void MapFile::offsetIndexBy(const int amount)
{
	index_ += amount;

	// circulate
	if (index_ < 0)
		index_ = paths_.size() - 1;
	else if (index_ >= static_cast<int>(paths_.size()))
		index_ = 0;

	// read map with new index
	load(paths_[index_]);
}

void MapFile::insertTile(const unsigned Yrow, const unsigned Xcol, const int tileIndex)
{
	if (Yrow < tiles_.size())
	{
		if (Xcol < tiles_[Yrow].size())
		{
			tiles_[Yrow][Xcol] = tileIndex;
		}
	}
	// TODO the rest


	
}
