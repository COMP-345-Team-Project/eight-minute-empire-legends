#pragma once

#include "MapLoaderTests.h"

#include "../../Core/Map/Map.h"
#include "../../Core/MapLoader/MapLoader.h"
#include <direct.h>
#define GetCurrentDir _getcwd

//The file is stored in \eight-minute-empire-legends\EightMinuteEmpireLegends\Debug, make sure you have the map1.json file there
std::string get_current_dir() {
	char buff[FILENAME_MAX]; //create string buffer to hold path
	GetCurrentDir(buff, FILENAME_MAX);
	string current_working_dir(buff);
	return current_working_dir;
}

// TODO: Make test function names more descriptive.
int MapLoaderTests::Test_LoadValidMap_Successful()
{
	std::cout << get_current_dir() << std::endl;
	std::cout << "Load a valid map file..." << std::endl;
	Map* map1 = MapLoader::parseMap("./MapLoaderTests/Resources/validJson_validMap_simple.json");
	delete map1;
	return 0;
}

int MapLoaderTests::Test_LoadValidMap2_Successful()
{
	std::cout << "\nLoad a valid map file..." << std::endl;
	Map* map2 = MapLoader::parseMap("./MapLoaderTests/Resources/validJson_validMap.json");
	delete map2;
	return 0;
}

int MapLoaderTests::Test_LoadIncorrectFileFormat_ReturnsNullPointer()
{
	std::cout << "\nLoad a incorrect file format (CSV)..." << std::endl;
	Map* map3 = MapLoader::parseMap("./MapLoaderTests/Resources/wrongFormatFile.csv"); //Pointer will be null
	return 0;
}

int MapLoaderTests::Test_LoadJsonMissingContinents_WhatShouldHappen()
{
	std::cout << "\nLoad a json file, but with missing continents data..." << std::endl;
	Map* map4 = MapLoader::parseMap("./MapLoaderTests/Resources/invalidJson_missingContinents.json");
	return 0;
}

int MapLoaderTests::Test_LoadJsonMissingVertices_WhatShouldHappen()
{
	std::cout << "\nLoad a json file, but with missing vertices..." << std::endl;
	Map* map5 = MapLoader::parseMap("./MapLoaderTests/Resources/invalidJson_missingVertices.json");
	return 0;
}

int MapLoaderTests::Test_LoadJsonWrongDataType_WhatShouldHappen()
{
	std::cout << "\nLoad a json file, but with wrong data type..." << std::endl;
	Map* map6 = MapLoader::parseMap("./MapLoaderTests/Resources/invalidJson_wrongDataType.json");
	return 0;
}

int MapLoaderTests::Test_LoadJsonDisconnectedGraph_WhatShouldHappen()
{
	std::cout << "\nLoad a json file, but it is a disconnected graph..." << std::endl;
	Map* map7 = MapLoader::parseMap("./MapLoaderTests/Resources/validJson_invalidMap.json");
	return 0;
}
