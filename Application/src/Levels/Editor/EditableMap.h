#pragma once
#include "EditableMap.h"
#include "../Common/Map.h"
#include "../Common/GameDetails.h"

class EditableMap : public Map {
public:
	void setMapFile(const MapFile &mapFile);
private:
};