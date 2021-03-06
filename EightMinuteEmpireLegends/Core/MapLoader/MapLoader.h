#pragma once
#include "../pch.h"

#include "../Map/Map.h"

using std::string;
using std::vector;

class MapLoader
{
public:
	static Map* parseMap(string mapPath);
	static bool validateJson(string mapPath);

private:
	static Continent* getContinentByName(vector<Continent*> &continents, string &name);
};