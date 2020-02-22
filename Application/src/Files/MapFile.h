#pragma once
#include "NGin.h"
#include <fstream>

class MapFile : public ngin::FileReader {
public:
	// scans directory for loadable files
	// true if successful false if not
	void scanDir();

	void read();
	void read(const std::string& path);

	void save();

	std::string getFolderPath() const { return folderPath_; }
	std::string getThemeLocation() const { return themeLocation_; }
	std::string getMapName() const { return title_; }
	// returns size of ONE tile
	sf::Vector2f getTileSize() const { return tileSize_; }
	int getNumberOfMaps() const { return static_cast<int>(paths_.size()); }
	int getNRows() const { return static_cast<int>(tiles_.size()); }
	int getNColumns(int row) const { return static_cast<int>(tiles_[row].size());}
	int getMaxNColums() const;
	// WARNING TAKES THE Y COORDINATE FIRST (FROM VECTORS)
	unsigned getTileNum(const int row, const int col) const { return tiles_[row][col]; }

	void addNewTile(const unsigned tileIndex, const sf::Vector2i& vectorPos);

	void offsetIndexBy(const int indexOffset);

private:
	std::vector<std::string> paths_; // paths of map files
	int index_ = 0; // index of current map file

	std::string title_ = "" ; // name (inside) of current map file
	std::string themeLocation_ = "";
	std::string folderPath_ = "";

	sf::Vector2f tileSize_ = { 0.0F, 0.0F }; // size of one tile
	std::vector<std::vector<unsigned>> tiles_; // tile numbers
};