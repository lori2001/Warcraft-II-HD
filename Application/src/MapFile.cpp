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
	mapPath_ = path;

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
				if (findAndClear(input, titleKey_))
					title_ = input;
				// ------------------------------------------------

				// --- Size of one tile ---------------------------
				if (findAndClear(input, tileWidthKey_))
					tileSize_.x = std::stof(input);
				if (findAndClear(input, tileHeightKey_))
					tileSize_.y = std::stof(input);
				// ------------------------------------------------

				// --- Theme --------------------------------------
				if (findAndClear(input, themeLocationKey_)) {
					themeLocation_ = input;
				}
				// ------------------------------------------------

				// --- Tiles --------------------------------------
				if (findAndClear(input, tileStartKey_)) {
					bool goOn = true;
					do {
						goOn = !findAndClear(input, tileEndKey_);
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

void MapFile::saveAs(const std::string& path)
{
	// TODO: this sHIIIET
	std::ofstream out(path);

	if (tiles_.size() <= 0) {
		NG_LOG_ERROR("No tiles specified in faulty mapfile:", path);
	}

	if (out.is_open()) {
		out << titleKey_ << title_ << std::endl;
		out << themeLocationKey_ << themeLocation_ << std::endl;
		out << tileWidthKey_ << tileSize_.x << std::endl;
		out << tileHeightKey_ << tileSize_.y << std::endl;

		out << tileStartKey_ << std::endl;
		for (int y = 0; y < static_cast<int>(tiles_.size()); y++) {
			for (int x = 0; x < static_cast<int>(tiles_[y].size()); x++) {
				out << tiles_[y][x] << " ";
			}
			out << std::endl;
		}
		out << tileEndKey_ << std::endl;
	}
	else {
		NG_LOG_ERROR("Unable To save file: ", path);
	}

	out.close();
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

MapFile::INSERT_RET MapFile::insertTile(const unsigned Xcol, const unsigned Yrow, const int tileIndex)
{
	if(tileIndex == 0)
		return INSERT_RET::NOT_OK;

	if (Yrow == -1)
	{
		if (Xcol == -1)
		{
			for (int i = 0; i < static_cast<int>(tiles_.size()); i++) // create "empty col"
				tiles_[i].insert(tiles_[i].begin(), placeholderTileNum_);
			
			std::vector<unsigned> temp; // create an empty new line
			temp.push_back(tileIndex); // add to first index
			tiles_.insert(tiles_.begin(), temp); // add temp as first row
			return INSERT_RET::X_NEGATIVE_Y_NEGATIVE;
		}
		else if (Xcol < tiles_[0].size())
		{
			std::vector<unsigned> temp(Xcol, placeholderTileNum_); // create an empty new line with size of X-pos
			temp.push_back(tileIndex); // push back tile index to temp 
			tiles_.insert(tiles_.begin(), temp); // add temp as first row
			return INSERT_RET::X_OK_Y_NEGATIVE;
		}
		else if (Xcol == tiles_[0].size())
		{
			std::vector<unsigned> temp(Xcol, placeholderTileNum_); // create an empty new line with size of X-pos
			temp.push_back(tileIndex); // push back tile index to temp 
			tiles_.insert(tiles_.begin(), temp); // add temp as first row
			return INSERT_RET::X_TOO_BIG_Y_NEGATIVE;
		}
	}
	else if (Yrow < tiles_.size())
	{
		if (Xcol == -1)
		{
			for (int i = 0; i < static_cast<int>(tiles_.size()); i++) {
				tiles_[i].insert(tiles_[i].begin(), placeholderTileNum_);
			}
			tiles_[Yrow][0] = tileIndex;
			return INSERT_RET::X_NEGATIVE_Y_OK;
		}
		else if (Xcol < tiles_[Yrow].size())
		{
			tiles_[Yrow][Xcol] = tileIndex;
			return INSERT_RET::ALL_OK;
		}
		else if (Xcol == tiles_[Yrow].size())
		{
			tiles_[Yrow].push_back(tileIndex);
			return INSERT_RET::X_TOO_BIG_Y_OK;
		}
	}
	else if (Yrow == tiles_.size())
	{
		if (Xcol == -1)
		{
			for (int i = 0; i < static_cast<int>(tiles_.size()); i++)
				tiles_[i].insert(tiles_[i].begin(), placeholderTileNum_);

			std::vector<unsigned> temp;
			temp.push_back(tileIndex);
			tiles_.push_back(temp);
			return INSERT_RET::X_NEGATIVE_Y_TOO_BIG;
		}
		else if (Xcol < tiles_[Yrow - 1].size())
		{
			std::vector<unsigned> temp(Xcol, placeholderTileNum_);
			temp.push_back(tileIndex);
			tiles_.push_back(temp);
			return INSERT_RET::X_OK_Y_TOO_BIG;
		}
		else if (Xcol == tiles_[Yrow - 1].size())
		{
			std::vector<unsigned> temp(Xcol, placeholderTileNum_);
			temp.push_back(tileIndex);
			tiles_.push_back(temp);
			return INSERT_RET::X_TOO_BIG_Y_TOO_BIG;
		}
	}
	
	return INSERT_RET::NOT_OK;
}
