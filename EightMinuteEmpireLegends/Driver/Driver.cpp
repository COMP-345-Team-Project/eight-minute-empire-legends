#pragma once

#include "Driver.h"
#include "AssignmentOneDriver.h"
#include "AssignmentTwoDriver.h"

int Driver::RunAssignmentOneDriver()
{
	AssignmentOneDriver ass1Driver;
	std::cout << "(1) Running the Map Driver..." << std::endl;
	ass1Driver.RunMapDriver();
	std::cout << "\n(2) Running the Map Loader Driver..." << std::endl;
	ass1Driver.RunMapLoaderDriver();
	std::cout << "\n(3) Running the Player Driver..." << std::endl;
	ass1Driver.RunPlayerDriver();
	std::cout << "\n(4) Running the Card Driver..." << std::endl;
	ass1Driver.RunCardsDriver();
	std::cout << "\n(5) Running the Bidding Facility Driver (the driver uses assertions so there will be no output)..." << std::endl;
	ass1Driver.RunBiddingFacilityDriver();
	return 0;
}

int Driver::RunAssignmentTwoDriver()
{
	AssignmentTwoDriver ass2Driver;

	//The main driver to run the game, show casing all of its functionality
	ass2Driver.RunGame();

	//Below here we have included mini-drivers to show case specific functionalities of the game
	/*std::cout << "(1) Running the Game Start Driver..." << std::endl;
	ass2Driver.RunGameStartDriver();
	std::cout << "(2 & 3 & 5) Running the Setup Phase and Main Game Loop Driver..." << std::endl;
	ass2Driver.RunSetupPhaseAndMainLoopDriver();
	std::cout << "(4) Running the Player Driver..." << std::endl;
	ass2Driver.RunPlayerDriver();*/
	//std::cout << "(6) Running the Computer Score Driver..." << std::endl;
	//ass2Driver.RunComputeScoreTest();
	
	return 0;
}


#include "../Core/GameCore/GameCore.h"
#include "../Core/GameCore/GameBuilder.h"
#include "../Core/MapLoader/MapLoader.h"

int Driver::RunStrategyDriver() {

	std::vector<std::string> names{ "AAA", "BBB", "CCC" };
	std::string mapPath = "..\\Tests\\SetupPhaseTests\\Resources\\narrows.json";
	Game* validGame = GameBuilder::build(3, names, mapPath);
	PlayerBuilder::setPlayersType(validGame->getPlayers());	
	//Temporarily set up a starting region to test code
	Vertex* startingRegion = validGame->FindVertexById(validGame->getMap(), "v3");
	validGame->getMap()->setStartingRegion(startingRegion);
	startingRegion->getTerritory()->setArmiesByPlayer(4, "Coucou");
	validGame->runSetupPhase();
	validGame->runRoundsUntilEndGame();
	return 0;
}
