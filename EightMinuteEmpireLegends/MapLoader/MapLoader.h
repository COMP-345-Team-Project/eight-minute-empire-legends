#pragma once
#include "Map.h"

using std::string;

class MapLoader
{
public:
	MapLoader();

	//Map loadMap();
	bool validateMap(string mapPath);
	Map parseMap(string mapPath);

private:
	Continent* getContinentByName(vector<Continent*> &continents, string &name);
};