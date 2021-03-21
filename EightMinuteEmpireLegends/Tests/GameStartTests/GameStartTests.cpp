#pragma once

#include "../../Core/GameCore/GameCore.h"
#include "../../Core/MapLoader/MapLoader.h"
#include "GameStartTests.h"

int GameStart::Test_ReadConfigFile() {
	std::string path = "./../../config/EightMinuteEmpireLengendsPrefs.ini";
	std::tuple<int, int, int> rsc;
	try {
		rsc = fetchConfigResources(path);		
	}
	catch (ConfigFileException& e) {
		std::cout << e.what() << std::endl;
	}	
	std::cout << ".INI resources are \nrCoins : " << get<0>(rsc) << " rArmies : " << get<1>(rsc) << " rCities : " << get<2>(rsc) << std::endl;
	return (get<0>(rsc) > 0 && get<1>(rsc) > 0 && get<2>(rsc) > 0) ? 0 : 1;
}

int GameStart::Test_MissingConfigFile() {
	std::string path = "./wrong-path/EightMinuteEmpireLengendsPrefs.ini";
	std::tuple<int, int, int> rsc;
	try {
		rsc = fetchConfigResources(path);
	}
	catch (ConfigFileException& e) {
		std::cout << e.what() << std::endl;
	}
	std::cout << ".INI resources are \nrCoins : " << get<0>(rsc) << " rArmies : " << get<1>(rsc) << " rCities : " << get<2>(rsc) << std::endl;
	return (get<0>(rsc) <= 0 && get<1>(rsc) <= 0 && get<2>(rsc) <= 0) ? 0 : 1;
}

int GameStart::Test_BuildGame() {
	int numPlayers = 2;
	Map* map = MapLoader::parseMap("./Resources/narrows.json");
	Game* validGame = GameBuilder::build(numPlayers, *map);

	int result = (map != NULL && map->validate() && validGame != NULL) ? 0 : 1;
	delete map;
	
	return result;
}
