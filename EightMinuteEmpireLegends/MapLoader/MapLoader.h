#pragma once
#include "Map.h"

class MapLoader
{
public:
	MapLoader();

	//Map loadMap();
	bool validateMap(string mapPath);
	void parseMap(string mapPath);
};