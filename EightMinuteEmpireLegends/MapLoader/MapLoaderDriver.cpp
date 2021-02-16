#pragma once
#include "MapLoader.h"
#include <iostream>
#include <fstream>

int main() {
	MapLoader map;

	//The file is stored in \eight-minute-empire-legends\EightMinuteEmpireLegends\Debug, make sure you have the map1.json file there
	std::cout << "Load a valid map file..." << std::endl;
	map.parseMap("map2.json");

	std::cout << "\nLoad a incorrect file format (CSV)..." << std::endl;
	map.parseMap("wrongFormatFile.csv");

	std::cout << "\nLoad a json file, but with invalid data..." << std::endl;
	map.parseMap("invalidJson_missingContinents.json");

	std::cout << "\nLoad a json file, but with no vertices data..." << std::endl;
	map.parseMap("invalidJson_missingVertices.json");

	std::cout << "\nLoad a json file, but it is a disconnected graph..." << std::endl;
	map.parseMap("validJson_invalidMap.json");

	return 0;
}

