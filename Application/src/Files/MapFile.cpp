#include "MapFile.h"
#include <iostream>
#include <filesystem>

void MapFile::scanDir()
{
	// Secure cleanup
	paths_.clear();
	folderPath_ = "";

	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, sizeof(buffer));

	std::string::size_type pos = std::string(buffer).find_last_of("\\/");
	folderPath_ = std::string(buffer).substr(0, pos) + "\\assets\\maps";

	try {
		for (const auto& entry : std::filesystem::directory_iterator(folderPath_)) {
			std::string temp = entry.path().u8string();

			// only load .txt files
			std::size_t found = temp.find_last_of(".");
			if (temp.substr(found) == ".mapfile") {
				paths_.push_back(entry.path().u8string());
			}
		}
	}
	catch (...) {
		NG_LOG_ERROR("Directory expected to contain .mapfile files has not been found: \n ",
			folderPath_ , " -- Please create directory!");
		std::abort();
	}
}

void MapFile::read()
{
	if (paths_.size() > 0) {
		read(paths_[index_]);
	}
	else {
		NG_LOG_ERROR("No maps found in assets/maps/ !");
		std::abort();
	}
}

void MapFile::read(const std::string& path)
{
	std::ifstream in(path);

	if (in.is_open()) {
		std::string input;

		// clear up
		tiles_.clear();
		tileSize_ = -1;
		themeLocation_ = "";
		title_ = "";

		while (std::getline(in, input)) {

			// clears white lines and comments
			auto inputType = cleanInput(input);

			if (inputType == ngin::FileReader::INPUT_TYPE::OK)
			{
				// --- Map Name -----------------------------------
				if (findAndClear(input, "Title: "))
					title_ = input;
				// ------------------------------------------------

				// --- Size of one tile ---------------------------
				if (findAndClear(input, "TileSize:"))
					tileSize_ = std::stoi(input);
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

						if (inputType == ngin::FileReader::INPUT_TYPE::OK)
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
	in.close();
}

void MapFile::save()
{
}

int MapFile::getMaxNColums() const
{
	unsigned maxSize = 0;

	for (int i = 0; i < int(tiles_.size()); i++) {
		if (maxSize < tiles_[i].size()) {
			maxSize = tiles_[i].size();
		}
	}

	return static_cast<int>(maxSize);
}

void MapFile::offsetIndexBy(const int indexOffset)
{
	index_ += indexOffset;

	// circulate
	if (index_ < 0)
		index_ = paths_.size() - 1;
	else if (index_ >= static_cast<int>(paths_.size()))
		index_ = 0;

	// Re-read map
	read();
}