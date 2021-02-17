#pragma once
#include "../Map/Map.h"
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
	Map* map1 = mapLoader.parseMap("./Resources/test.json");
	std::cout << validateMap(map1) << std::endl;
	delete map1;

	std::cout << "\nLoad a valid map file..." << std::endl;
	Map* map2 = mapLoader.parseMap("./Resources/validJson_validMap.json");
	std::cout << validateMap(map2) << std::endl;
	delete map2;
	
	std::cout << "\nLoad a incorrect file format (CSV)..." << std::endl;
	Map* map3 = mapLoader.parseMap("./Resources/wrongFormatFile.csv");
	std::cout << validateMap(map3) << std::endl;
	delete map3;

	std::cout << "\nLoad a json file, but with missing continents data..." << std::endl;
	Map* map4 = mapLoader.parseMap("./Resources/invalidJson_missingContinents.json");
	delete map4;

	std::cout << "\nLoad a json file, but with missing vertices..." << std::endl;
	Map* map5 = mapLoader.parseMap("./Resources/invalidJson_missingVertices.json");
	delete map5;

	std::cout << "\nLoad a json file, but with wrong data type..." << std::endl;
	Map* map6 = mapLoader.parseMap("./Resources/invalidJson_wrongDataType.json");
	delete map6;

	std::cout << "\nLoad a json file, but it is a disconnected graph..." << std::endl;
	Map* map7 = mapLoader.parseMap("./Resources/validJson_invalidMap.json");
	std::cout << validateMap(map7) << std::endl;
	delete map7;

	return 0;
}


