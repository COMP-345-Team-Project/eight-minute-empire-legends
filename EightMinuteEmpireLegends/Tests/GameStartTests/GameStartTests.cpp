#pragma once

#include "../../Core/GameCore/GameBuilder.h"
#include "../../Core/GameCore/GameCore.h"
#include "../../Core/MapLoader/MapLoader.h"
#include "../../Core/MapLoader/MapLoaderException.h"
#include "GameStartTests.h"

// Tests fetching and reading configuration file. Success case.
int GameStart::Test_ReadConfigFile_Success() {
	std::tuple<int, int, int> rsc;
	try {
		rsc = fetchConfigResources(_configPath);
	}
	catch (ConfigFileException& e) {
		std::cout << e.what() << std::endl;
	}
	std::cout << ".INI resources are \nrCoins : " << get<0>(rsc) << " rArmies : " << get<1>(rsc) << " rCities : " << get<2>(rsc) << std::endl;
	assert(get<0>(rsc) > 0 && get<1>(rsc) > 0 && get<2>(rsc) > 0);
	Passed("Test_ReadConfigFile_Success()");
	return 0;
}

// Tests fetching and reading configuration file. Failed case.
int GameStart::Test_ReadConfigFile_Failure() {
	std::string path = "./wrong-path/EightMinuteEmpireLengendsPrefs.ini";
	std::tuple<int, int, int> rsc;
	try {
		rsc = fetchConfigResources(path);
	}
	catch (ConfigFileException& e) {
		std::cout << e.what() << std::endl;
	}
	std::cout << ".INI resources are \nrCoins : " << get<0>(rsc) << " rArmies : " << get<1>(rsc) << " rCities : " << get<2>(rsc) << std::endl;
	assert(get<0>(rsc) <= 0 && get<1>(rsc) <= 0 && get<2>(rsc) <= 0);
	Passed("Test_ReadConfigFile_Failure()");
	return 0;
}

// Tests accepting player input for selecting player count. Success case.
int GameStart::Test_PlayerInput_SelectPlayerCount_ValidEntry() {
	int numPlayers;	
	std::cout << "Enter 3" << std::endl;
	std::cout << "Please enter the number of players (2-4) : ";
	std::cin >> numPlayers;
	if (numPlayers >= 2 && numPlayers <= 4) {
		std::cout << "This game is set to " << numPlayers << " players." << std::endl;
	}
	assert(numPlayers >= 2 && numPlayers <= 4);
	Passed("Test_PlayerInput_SelectPlayerCount_ValidEntry()");
	return 0;
}

// Tests accepting player input for selecting player count. Failed case.
int GameStart::Test_PlayerInput_SelectPlayerCount_InvalidEntry() {
	int numPlayers;
	std::cout << "Enter 5" << std::endl;
	std::cout << "Please enter the number of players (2-4) : ";	
	std::cin >> numPlayers;
	if (numPlayers < 2 || numPlayers > 4) {
		std::cout << "Invalid entry. Defaulting to 2 players." << std::endl;
		numPlayers = 2;
	}
	assert(numPlayers == 2);
	Passed("Test_PlayerInput_SelectPlayerCount_InvalidEntry()");
	return 0;
}

// Tests accepting player input for selecting map. Success case.
int GameStart::Test_PlayerInput_MapSelect_ValidEntry() {	
	std::vector<filesystem::path> maps{};	
	std::cout << "Enter 0" << std::endl;
	std::cout << "Please select a map.\n" << std::endl;	
	int index = 0;
	int selection;
	for (const auto& entry : filesystem::directory_iterator(_mapDir)) {
		maps.push_back(entry.path());
		std::cout << index << ") " << entry.path().filename() << std::endl;
		index++;
	}
	std::cin >> selection;
	assert(selection >= 0 && selection < index);
	std::cout << "Map " << maps.at(selection).filename() << " was chosen." << std::endl;
	Passed("Test_PlayerInput_MapSelect_Success()");
	return 0;
}

// Tests accepting player input for selecting map. Failed case.
int GameStart::Test_PlayerInput_MapSelect_InvalidEntry() {	
	std::vector<filesystem::path> maps{};
	std::cout << "Enter 5" << std::endl;
	std::cout << "Please select an invalid map number.\n" << std::endl;
	int index = 0;
	int selection;
	for (const auto& entry : filesystem::directory_iterator(_mapDir)) {
		maps.push_back(entry.path());
		std::cout << index << ") " << entry.path().filename() << std::endl;
		index++;
	}
	std::cin >> selection;
	assert(selection < 0 || selection >= index);
	std::cout << "Invalid Entry" << std::endl;
	Passed("Test_PlayerInput_MapSelect_Failure()");
	return 0;
}

// Tests building game. Success case.
int GameStart::Test_BuildGame_Success() {
	int numPlayers = 2;
	std::vector<std::string> names{ "Player 1", "Player 2" };	
	std::string mapPath = _mapDir + "\\narrows.json";
	Game* validGame = GameBuilder::build(numPlayers, names, mapPath);
	assert(validGame->getMap() != NULL);
	delete validGame;
	Passed("Test_BuildGame_Success()");
	return 0;
}

// Tests building game. Failed case.
int GameStart::Test_BuildGame_Failure() {
	int numPlayers = 2;
	std::vector<std::string> names{ "Player 1", "Player 2" };
	std::string mapPath = "./wrong-path/Resources/narrows.json";
	Game* validGame = GameBuilder::build(numPlayers, names, mapPath);
	assert(validGame->getMap() == NULL);
	delete validGame;
	Passed("Test_BuildGame_Failure()");
	return 0;
}

int GameStart::Demo_BuildGame() {
	std::cout << "--- Game Builder Demo --- " << std::endl;
	try {
		Game* game = GameBuilder::build(); //The creation is handled here including getting user input
		std::cout << game;
	}
	catch (GameBuilderException& e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}

int GameStart::Demo_DisplayTerritories() {
	int numPlayers = 4;
	std::vector<std::string> names{ "Player 1", "Player 2", "Player 3", "Player 4" };
	// ./GameStartTests/Resources/narrows.json
	std::string mapPath = _mapDir + "\\narrows.json";
	Game* validGame = GameBuilder::build(numPlayers, names, mapPath);	
	validGame->displayTerritories(validGame->getMap()->vertices());

	return 0;
}

void GameStart::Passed(std::string testName) {
	std::cout << std::endl << testName << " >> Passed\n" << std::endl;
}
