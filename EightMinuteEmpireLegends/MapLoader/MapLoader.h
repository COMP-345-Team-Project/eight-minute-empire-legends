#pragma once
#include "../Map/Map.h"

using std::string;
using std::vector;

class MapLoader
{
public:
	MapLoader();
	Map* parseMap(string mapPath);
	bool validateJson(string mapPath);

private:
	Continent* getContinentByName(vector<Continent*> &continents, string &name);
};