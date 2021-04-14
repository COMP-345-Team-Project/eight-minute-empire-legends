#include "SetupPhaseTests.h"

#include "../../Core/GameCore/GameCore.h"
#include "../../Core/GameCore/GameBuilder.h"
#include "../../Core/MapLoader/MapLoader.h"


void SetupPhaseTests::Test_SetupPhaseAndGameLoopExecutes_GivenValidInput()
{
	std::vector<std::string> names{ "Coucou", "Banane" };
	std::string mapPath = "..\\Tests\\SetupPhaseTests\\Resources\\narrows.json";
	Game* validGame = GameBuilder::build(2, names, mapPath);

	//Temporarily set up a starting region to test code
	Vertex* startingRegion = validGame->FindVertexById(validGame->getMap(), "v3");
	validGame->getMap()->setStartingRegion(startingRegion);
	startingRegion->getTerritory()->setArmiesByPlayer(4, "Coucou");

	validGame->runSetupPhase();
	validGame->runRoundsUntilEndGame();
}

void SetupPhaseTests::Test_PlaceArmies()
{
	std::cout << "Testing PlacingArmies() Console " << std::endl;
	std::vector<std::string> names{ "Coucou", "Banane" };
	std::string mapPath = "..\\Tests\\SetupPhaseTests\\Resources\\narrows.json";
	Game* validGame = GameBuilder::build(2, names, mapPath);

	//Temporarily set up a starting region to test code
	Vertex* startingRegion = validGame->FindVertexById(validGame->getMap(), "v3");
	validGame->getMap()->setStartingRegion(startingRegion);

	validGame->_assignResources();
	validGame->PlaceArmies(validGame->getPlayers().at(0), 4);
}

void SetupPhaseTests::Test_MoveArmies()
{
	std::cout << "Testing MoveArmies() Console " << std::endl;
	std::vector<std::string> names{ "Coucou", "Banane" };
	std::string mapPath = "..\\Tests\\SetupPhaseTests\\Resources\\narrows.json";
	Game* validGame = GameBuilder::build(2, names, mapPath);

	//Temporarily set up a starting region to test code and assign player Coucou some armies
	Vertex* startingRegion = validGame->FindVertexById(validGame->getMap(), "v3");
	validGame->getMap()->setStartingRegion(startingRegion);
	startingRegion->getTerritory()->setArmiesByPlayer(4, "Coucou");

	validGame->_assignResources();
	validGame->MoveArmies(validGame->getPlayers().at(0), 4);
}

void SetupPhaseTests::Test_BuildCity()
{
	std::cout << "Testing BuildCity() Console " << std::endl;
	std::vector<std::string> names{ "Coucou", "Banane" };
	std::string mapPath = "..\\Tests\\SetupPhaseTests\\Resources\\narrows.json";
	Game* validGame = GameBuilder::build(2, names, mapPath);

	//Temporarily set up a starting region to test code and assign player Coucou some armies
	Vertex* startingRegion = validGame->FindVertexById(validGame->getMap(), "v3");
	validGame->getMap()->setStartingRegion(startingRegion);
	startingRegion->getTerritory()->setArmiesByPlayer(4, "Coucou");

	validGame->_assignResources();
	validGame->BuildCity(validGame->getPlayers().at(0));
	assert(startingRegion->getTerritory()->getCitiesByPlayer("Coucou") == 1);
}

void SetupPhaseTests::Test_DestroyArmies()
{
	std::cout << "Testing DestroyArmies() Console " << std::endl;
	std::vector<std::string> names{ "Coucou", "Banane" };
	std::string mapPath = "..\\Tests\\SetupPhaseTests\\Resources\\narrows.json";
	Game* validGame = GameBuilder::build(2, names, mapPath);
	validGame->_assignResources();

	//Temporarily set up a starting region to test code and assign player Coucou some armies
	Vertex* startingRegion = validGame->FindVertexById(validGame->getMap(), "v3");
	validGame->getMap()->setStartingRegion(startingRegion);
	Player* p1 = validGame->getPlayers().at(0);
	Player* p2 = validGame->getPlayers().at(1);
	p1->PlaceNewArmies(validGame->getMap(), startingRegion, 3);
	p2->PlaceNewArmies(validGame->getMap(), startingRegion, 3);

	validGame->DestroyArmies(p1, 3);
}
