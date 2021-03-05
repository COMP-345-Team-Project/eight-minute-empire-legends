#pragma once
#include "MapLoaderTests.h"
//The file is stored in \eight-minute-empire-legends\EightMinuteEmpireLegends\Debug, make sure you have the map1.json file there


// TODO: Make test function names more descriptive.
int MapLoaderTests::Test_LoadValidMap_Successful()
{
	std::cout << "Load a valid map file..." << std::endl;
	Map* map1 = MapLoader::parseMap("./Resources/validJson_validMap_simple.json");
	delete map1;
	return 0;
}

int MapLoaderTests::Test_LoadValidMap2_Successful()
{
	std::cout << "\nLoad a valid map file..." << std::endl;
	Map* map2 = MapLoader::parseMap("./Resources/validJson_validMap.json");
	delete map2;
	return 0;
}

int MapLoaderTests::Test_LoadIncorrectFileFormat_ReturnsNullPointer()
{
	std::cout << "\nLoad a incorrect file format (CSV)..." << std::endl;
	Map* map3 = MapLoader::parseMap("./Resources/wrongFormatFile.csv"); //Pointer will be null
	return 0;
}

int MapLoaderTests::Test_LoadJsonMissingContinents_WhatShouldHappen()
{
	std::cout << "\nLoad a json file, but with missing continents data..." << std::endl;
	Map* map4 = MapLoader::parseMap("./Resources/invalidJson_missingContinents.json");
	return 0;
}

int MapLoaderTests::Test_LoadJsonMissingVertices_WhatShouldHappen()
{
	std::cout << "\nLoad a json file, but with missing vertices..." << std::endl;
	Map* map5 = MapLoader::parseMap("./Resources/invalidJson_missingVertices.json");
	return 0;
}

int MapLoaderTests::Test_LoadJsonWrongDataType_WhatShouldHappen()
{
	std::cout << "\nLoad a json file, but with wrong data type..." << std::endl;
	Map* map6 = MapLoader::parseMap("./Resources/invalidJson_wrongDataType.json");
	return 0;
}

int MapLoaderTests::Test_LoadJsonDisconnectedGraph_WhatShouldHappen()
{
	std::cout << "\nLoad a json file, but it is a disconnected graph..." << std::endl;
	Map* map7 = MapLoader::parseMap("./Resources/validJson_invalidMap.json");
	return 0;
}
