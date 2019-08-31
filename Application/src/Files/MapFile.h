#pragma once
#include "NGin.h"
#include <fstream>

class MapFile : public ngin::FileReader {
public:

	// scans directory and saves loadable files
	void scanDir();

	void read();
	void read(const std::string& path);

	void save();

	std::string getFolderPath() const { return folderPath_; }
	std::string getThemeLocation() const { return themeLocation_; }
	std::string getMapName() const { return title_; }
	int getNumberOfMaps() const { return static_cast<int>(paths_.size()); }
	int getNRows() const { return static_cast<int>(tiles_.size()); }
	int getNColumns(int row) const { return static_cast<int>(tiles_[row].size());}
	int getTileSize() const { return tileSize_; }
	int getMaxNColums() const;
	unsigned getTileNum(const int row, const int col) const { return tiles_[row][col]; }

	void offsetIndexBy(const int indexOffset);
private:
	std::vector<std::string> paths_; // paths of map files
	int index_ = 0; // index of current map file

	std::string title_ = "" ; // name (inside) of current map file
	std::string themeLocation_ = "";
	std::string folderPath_ = "";

	int tileSize_ = -1; // size of one tile
	std::vector<std::vector<unsigned>> tiles_; // tile numbers
};