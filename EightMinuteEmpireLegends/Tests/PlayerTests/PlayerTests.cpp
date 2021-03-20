#pragma once

#include "PlayerTests.h"

#include "../../Core/Player/Player.h"
#include "../../Core/Bidding/BidTieBreakerByLastName.h"
#include "../../Core/MapLoader/MapLoader.h"

//Test constants
const int numOfArmiesToDeploy = 1;
const int badNumOfArmiesToDeploy = 0;
const int numOfCoins = 11;
const int numOfArmies = 10;
const int numOfCities = 3;
const string playerName = "player1";

Vertex* findVertexById(Map* map, string id) {
	vector<Vertex*> vertices = map->vertices();
	for (vector<Vertex*>::iterator vertexIter = vertices.begin(); vertexIter != vertices.end(); vertexIter++) {
		if ((**vertexIter).getId().compare(id) == 0)
			return *vertexIter;
	}
}

int PlayerTests::Test_PlayerFunctionsExecute()
{	
	Map* map = MapLoader::parseMap("C:/Users/thuan/Desktop/STUDY/COMP 345/eight-minute-empire-legends/EightMinuteEmpireLegends/Tests/MapLoaderTests/Resources/validJson_validMap.json");
	BidTieBreakerByLastName bidTieBreakerByLastName;
	BiddingFacility biddingFacility(bidTieBreakerByLastName);
	Player* p1 = new Player("player1", biddingFacility);

	//Arrange
	//Set the starting region
	Vertex* startingRegion = findVertexById(map, "1");
	map->setStartingRegion(startingRegion);
	std::cout << "Starting region:" << std::endl;
	std::cout << map->getStartingRegion() << std::endl;
	//Build a city on a specific region
	Vertex* regionWithCity = findVertexById(map, "2");
	regionWithCity->getTerritory()->addCitiesByPlayer(1, "player1");
	//Get a region without a city
	Vertex*  regionWithoutCity = findVertexById(map, "3");

	//Testing errorneous cases
	//Negative number of armes error
	bool errorCaught = false;
	try {
		p1->PlaceNewArmies(map, startingRegion, badNumOfArmiesToDeploy);
	}
	catch (PlayerActionException& ex) {
		errorCaught = true;
	}
	assert(errorCaught == true);
	
	//Not enough armies to deploy
	errorCaught = false;
	try {
		p1->PlaceNewArmies(map, regionWithCity, numOfArmiesToDeploy);
	}
	catch (PlayerActionException& ex) {
		errorCaught = true;
	}
	assert(errorCaught == true);
	errorCaught = false;

	//Not deploying in a starting region, or with city built
	errorCaught = false;
	p1->InitResources(numOfCoins, numOfArmies, numOfCities);
	try {
		p1->PlaceNewArmies(map, regionWithoutCity, numOfArmiesToDeploy);
	}
	catch (PlayerActionException& ex) {
		errorCaught = true;
	}
	assert(errorCaught == true);
	errorCaught = false;

	//Deploying in starting region, no error expected
	p1->PlaceNewArmies(map, startingRegion, numOfArmiesToDeploy);
	//Deploying in region with city, no error expected
	p1->PlaceNewArmies(map, regionWithCity, numOfArmiesToDeploy);

	//Assert
	assert(startingRegion->getTerritory()->getArmiesByPlayer("player1") == numOfArmiesToDeploy);
	assert(regionWithCity->getTerritory()->getArmiesByPlayer("player1") == numOfArmiesToDeploy);
	assert(p1->getAvailableArmies() == (numOfArmies - (numOfArmiesToDeploy + numOfArmiesToDeploy)));


	//delete p1;
	return 0;
}



/*int PlayerTests::Test_PlayerComputeScoreFunctionsExecute() {
	//Create map
	std::cout << "Load a valid map file..." << std::endl;
	Map* map = MapLoader::parseMap("./MapLoaderTests/Resources/validJson_validMap.json");
	
	Deck deck(2);
	BidTieBreakerByLastName bidTieBreakerByLastName;
	Player* p1 = new Player("player1", deck, bidTieBreakerByLastName);
	Player* p2 = new Player("player2", deck, bidTieBreakerByLastName);

	//Assign some regions to players
	Vertex* v0 = findVertexById(map, "0");
	p1->PlaceNewArmies(map, v0, 2);

	p1->BuildCity();
	p1->DestroyArmy();
	p1->MoveArmies();
	p1->MoveOverLand();
	p1->payCoin();
	p1->PlaceNewArmies();

	delete p1;
	delete p2;
	delete map;
	return 0;
}*/