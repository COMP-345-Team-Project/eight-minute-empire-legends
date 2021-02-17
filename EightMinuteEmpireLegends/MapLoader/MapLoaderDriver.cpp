#pragma once
#include "MapLoader.h"
#include <iostream>
#include <fstream>

string validateMap(Map* map) {
	if (!map->validate()) {
		return "The map is not a valid graph";
	}
	else {
		return "The map is a valid graph";
	}
}

int main() {
	MapLoader mapLoader;

	//The file is stored in \eight-minute-empire-legends\EightMinuteEmpireLegends\Debug, make sure you have the map1.json file there
	std::cout << "Load a valid map file..." << std::endl;
	Map* map1 = mapLoader.parseMap("test.json");
	std::cout << "Number of vertices: " + std::to_string(map1->vertices().size()) << std::endl;
	std::cout << validateMap(map1) << std::endl;
	
	std::cout << "\nLoad a incorrect file format (CSV)..." << std::endl;
	mapLoader.parseMap("wrongFormatFile.csv");

	std::cout << "\nLoad a json file, but with missing continents data..." << std::endl;
	mapLoader.parseMap("invalidJson_missingContinents.json");

	std::cout << "\nLoad a json file, but with missing vertices..." << std::endl;
	mapLoader.parseMap("invalidJson_missingVertices.json");

	std::cout << "\nLoad a json file, but with wrong data type..." << std::endl;
	mapLoader.parseMap("invalidJson_wrongDataType.json");

	std::cout << "\nLoad a json file, but it is a disconnected graph..." << std::endl;
	mapLoader.parseMap("validJson_invalidMap.json");

	return 0;
}


