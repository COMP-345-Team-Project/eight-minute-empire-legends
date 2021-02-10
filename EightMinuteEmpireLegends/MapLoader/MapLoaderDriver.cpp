#pragma once
#include "MapLoader.h"
#include <iostream>
#include <fstream>

int main() {
	MapLoader map;

	//The file is stored in \eight-minute-empire-legends\EightMinuteEmpireLegends\Debug, make sure you have the map1.json file there
	bool valid = map.validateMap("map1.json");
	std:cout << valid;

	map.parseMap("map1.json");

	return 0;
}

