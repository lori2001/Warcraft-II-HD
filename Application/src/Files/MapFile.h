#pragma once
#include "NGin.h"
#include <fstream>

class MapFile : public ng::FileReader {
public:
	// scans directory for loadable files
	// true if successful false if not
	static bool scanDir();

	static void load(const std::string& path);
	static void load(const unsigned index = 0) {
		load(paths_[index]);
	}
	static void save();

	static constexpr const char* RELATIVE_FOLDER_PATH = "\\assets\\maps";
	static constexpr const char* MAP_FILE_EXTENSION = "mapfile"; // WARNING NO POINT AT BEGINNING!

	static const char* getFolderPath() {
		if (folderPath_ == "")
			throw("folder path accesed but not set!");
		else
			return folderPath_.c_str();
	}

	static std::string getThemeLocation() { return themeLocation_; }
	static std::string getMapName() { return title_; }
	static int getMapIndex() { return index_; }
	static sf::Vector2f getTileSize() { return tileSize_; } // returns size of ONE tile
	static int getNumberOfMaps() { return static_cast<int>(paths_.size()); }
	static int getNumOfRows() { return static_cast<int>(tiles_.size()); } // y
	static int getNumOfColumns(int row) { return static_cast<int>(tiles_[row].size()); } // x at (y)row
	static int getMaxNumOfColumns(); // max x

	static unsigned getTileNum(const int Xcol, const int Yrow) { return tiles_[Yrow][Xcol]; }

	// changes index by @param amount
	// (re)loads map internally
	static void offsetIndexBy(const int amount);

protected:
	enum class INSERT_RET {
		NOT_OK,
		ALL_OK,
		X_NEGATIVE_Y_NEGATIVE,
		X_NEGATIVE_Y_OK,
		X_NEGATIVE_Y_TOO_BIG,
		X_OK_Y_NEGATIVE,
		X_TOO_BIG_Y_NEGATIVE,
		X_TOO_BIG_Y_OK,
		X_TOO_BIG_Y_TOO_BIG,
		X_OK_Y_TOO_BIG
	};
	static INSERT_RET insertTile(const unsigned Xcol, const unsigned Yrow, const int tileIndex);

private:
	static inline std::vector<std::string> paths_; // paths of all map files
	static inline int index_ = 0; // index of current map file

	static inline std::string title_ = ""; // name (inside) of current map file
	static inline std::string themeLocation_ = "";
	static inline std::string folderPath_ = ""; // the folder in which mapfiles are located ()

	static inline sf::Vector2f tileSize_ = { 0.0F, 0.0F }; // size of one tile

	// 2D matrix of tiles
	// each number represents index in tile-file (numbered from left to right and beginning at newline)
	static inline std::vector<std::vector<unsigned>> tiles_;
};
