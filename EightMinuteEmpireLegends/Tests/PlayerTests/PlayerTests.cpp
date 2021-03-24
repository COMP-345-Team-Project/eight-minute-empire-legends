#pragma once

#include "PlayerTests.h"

#include "../../Core/Player/Player.h"
#include "../../Core/Bidding/BidTieBreakerByLastName.h"
#include "../../Core/MapLoader/MapLoader.h"

Vertex* findVertexById(Map* map, string id) {
	vector<Vertex*> vertices = map->vertices();
	for (vector<Vertex*>::iterator vertexIter = vertices.begin(); vertexIter != vertices.end(); vertexIter++) {
		if ((**vertexIter).getId().compare(id) == 0)
			return *vertexIter;
	}
}

PlayerTests::PlayerTests() {
	numOfArmiesToDeploy = 1;
	badNumOfArmiesToDeploy = 0;
	numOfCoins = 11;
	numOfArmies = 10;
	numOfCities = 3;
	playerName = "player1";
	//Temporary fix for the running directory issue, will be removed after
	mapPath = "C:/Users/thuan/Desktop/STUDY/COMP 345/eight-minute-empire-legends/EightMinuteEmpireLegends/Tests/MapLoaderTests/Resources/validJson_validMap.json";
}

int PlayerTests::Test_PlaceArmies()
{	
	Map* map = MapLoader::parseMap(mapPath);
	BidTieBreakerByLastName bidTieBreakerByLastName;
	BiddingFacility* biddingFacility = new BiddingFacility(bidTieBreakerByLastName);
	Player* p1 = new Player(playerName, biddingFacility);

	//Arrange
	//Set the starting region
	Vertex* startingRegion = findVertexById(map, "1");
	map->setStartingRegion(startingRegion);
	//Build a city on a specific region
	Vertex* regionWithCity = findVertexById(map, "2");
	regionWithCity->getTerritory()->addCitiesByPlayer(1, playerName);
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
		std::cout << ex.what() << std::endl;
	}
	assert(errorCaught == true);
	
	//Not enough armies to deploy
	errorCaught = false;
	try {
		p1->PlaceNewArmies(map, regionWithCity, numOfArmiesToDeploy);
	}
	catch (PlayerActionException& ex) {
		errorCaught = true;
		std::cout << ex.what() << std::endl;
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
		std::cout << ex.what() << std::endl;
	}
	assert(errorCaught == true);
	errorCaught = false;

	//Deploying in starting region, no error expected
	p1->PlaceNewArmies(map, startingRegion, numOfArmiesToDeploy);
	//Deploying in region with city, no error expected
	p1->PlaceNewArmies(map, regionWithCity, numOfArmiesToDeploy);

	//Assert
	assert(startingRegion->getTerritory()->getArmiesByPlayer(playerName) == numOfArmiesToDeploy);
	assert(regionWithCity->getTerritory()->getArmiesByPlayer(playerName) == numOfArmiesToDeploy);
	assert(p1->HasArmyDeployedInVertex(startingRegion));
	assert(p1->HasArmyDeployedInVertex(regionWithCity));
	assert(p1->HasArmyDeployedInVertex(regionWithoutCity) == false);
	assert(p1->getAvailableArmies() == (numOfArmies - (numOfArmiesToDeploy + numOfArmiesToDeploy)));

	delete biddingFacility;
	delete p1;
	delete map;
	return 0;
}

int PlayerTests::Test_MoveArmies() {
	std::cout << "Testing Player::MoveArmies()" << std::endl;
	Map* map = MapLoader::parseMap(mapPath);
	BidTieBreakerByLastName bidTieBreakerByLastName;
	BiddingFacility* biddingFacility = new BiddingFacility(bidTieBreakerByLastName);
	Player* p1 = new Player(playerName, biddingFacility);

	//Arrange
	//Set from region
	Vertex* fromRegion = findVertexById(map, "1");
	map->setStartingRegion(fromRegion);
	p1->InitResources(numOfCoins, numOfArmies, numOfCities);
	p1->PlaceNewArmies(map, fromRegion, 2);
	//Set the to region the move over land
	Vertex* toRegionLand = findVertexById(map, "0");
	//Set the to region the move over water
	Vertex* toRegionWater = findVertexById(map, "9");
	int remainingMoves = 0;

	//Testing errorneous cases
	std::cout << "Testing error cases, error messages will be output..." << std::endl;
	//From and To regions are the same
	bool errorCaught = false;
	try {
		p1->MoveArmies(map, fromRegion, fromRegion, 1, remainingMoves);
	}
	catch (PlayerActionException& ex) {
		errorCaught = true;
		std::cout << ex.what() << std::endl;
	}
	assert(errorCaught == true);

	//Number of armies to move exceeding available armies
	errorCaught = false;
	try {
		p1->MoveArmies(map, fromRegion, toRegionLand, 12, remainingMoves);
	}
	catch (PlayerActionException& ex) {
		errorCaught = true;
		std::cout << ex.what() << std::endl;
	}
	assert(errorCaught == true);

	//Not enough moves
	errorCaught = false;
	try {
		p1->MoveArmies(map, fromRegion, toRegionLand, 1, remainingMoves);
	}
	catch (PlayerActionException& ex) {
		errorCaught = true;
		std::cout << ex.what() << std::endl;
	}
	assert(errorCaught == true);

	//Testing correct cases
	std::cout << "Testing correct cases using assertions..." << std::endl;
	remainingMoves = 4;
	assert(p1->HasArmyDeployedInVertex(toRegionLand) == false);
	assert(p1->HasArmyDeployedInVertex(toRegionWater) == false);
	p1->MoveArmies(map, fromRegion, toRegionLand, 1, remainingMoves);
	assert(fromRegion->getTerritory()->getArmiesByPlayer(playerName) == 1);
	assert(toRegionLand->getTerritory()->getArmiesByPlayer(playerName) == 1);
	assert(remainingMoves == 3);
	assert(p1->HasArmyDeployedInVertex(fromRegion)); // 1 army left in the from region
	assert(p1->HasArmyDeployedInVertex(toRegionLand));
	p1->MoveArmies(map, fromRegion, toRegionWater, 1, remainingMoves);
	assert(fromRegion->getTerritory()->getArmiesByPlayer(playerName) == 0);
	assert(toRegionLand->getTerritory()->getArmiesByPlayer(playerName) == 1);
	assert(remainingMoves == 0);
	assert(p1->HasArmyDeployedInVertex(fromRegion) == false); // No more army left in the from region
	assert(p1->HasArmyDeployedInVertex(toRegionWater));

	delete biddingFacility;
	delete p1;
	delete map;
	return 0;
}

int PlayerTests::Test_DestroyArmies() {
	std::cout << "Testing Player::DestroyArmy()" << std::endl;
	Map* map = MapLoader::parseMap(mapPath);
	BidTieBreakerByLastName bidTieBreakerByLastName;
	BiddingFacility* biddingFacility = new BiddingFacility(bidTieBreakerByLastName);
	Player* p1 = new Player(playerName, biddingFacility);

	//Arrange
	//Set the starting region then set some armies at the starting region
	Vertex* region = findVertexById(map, "1");
	map->setStartingRegion(region);
	p1->InitResources(numOfCoins, numOfArmies, numOfCities);
	p1->PlaceNewArmies(map, region, 3);
	//Make sure that region is added to deployedVertices of the player
	assert(p1->HasArmyDeployedInVertex(region));

	//Testing errorneous cases
	std::cout << "Testing error cases, error messages will be output..." << std::endl;
	//Remove more than deployed
	bool errorCaught = false;
	try {
		p1->DestroyArmy(region, 4);
	}
	catch (PlayerActionException& ex) {
		errorCaught = true;
		std::cout << ex.what() << std::endl;
	}
	assert(errorCaught == true);

	//Testing correct cases
	std::cout << "Testing correct cases using assertions..." << std::endl;
	p1->DestroyArmy(region, 2);
	assert(region->getTerritory()->getArmiesByPlayer(playerName) == 1);
	assert(p1->getAvailableArmies() == 9);
	assert(p1->HasArmyDeployedInVertex(region)); //still has 1 army
	//Remove the last army
	p1->DestroyArmy(region, 1);
	assert(region->getTerritory()->getArmiesByPlayer(playerName) == 0);
	assert(p1->getAvailableArmies() == 10);
	assert(p1->HasArmyDeployedInVertex(region) == false); 

	delete biddingFacility;
	delete p1;
	delete map;
	return 0;
}

int PlayerTests::Test_PlaceCities() {
	std::cout << "Testing Player::DestroyArmy()" << std::endl;
	Map* map = MapLoader::parseMap(mapPath);
	BidTieBreakerByLastName bidTieBreakerByLastName;
	BiddingFacility* biddingFacility = new BiddingFacility(bidTieBreakerByLastName);
	Player* p1 = new Player(playerName, biddingFacility);

	//Arrange
	//Set the starting region then set some armies at the starting region
	Vertex* region = findVertexById(map, "1");
	map->setStartingRegion(region);

	//Testing errorneous cases
	std::cout << "Testing error cases, error messages will be output..." << std::endl;
	//Do not have enough cities to build
	bool errorCaught = false;
	try {
		p1->BuildCity(region, 1);
	}
	catch (PlayerActionException& ex) {
		errorCaught = true;
		std::cout << ex.what() << std::endl;
	}
	assert(errorCaught == true);

	p1->InitResources(numOfCoins, numOfArmies, numOfCities);
	//Region does not have armies
	errorCaught = false;
	try {
		p1->BuildCity(region, 1);
	}
	catch (PlayerActionException& ex) {
		errorCaught = true;
		std::cout << ex.what() << std::endl;
	}
	assert(errorCaught == true);

	std::cout << "Testing correct cases using assertions..." << std::endl;
	p1->PlaceNewArmies(map, region, 3);
	assert(p1->getAvailableCities() == 3);
	p1->BuildCity(region, 1);
	assert(p1->getAvailableCities() == 2);
	assert(region->getTerritory()->getCitiesByPlayer(playerName) ==  1);

	delete biddingFacility;
	delete p1;
	delete map;
	return 0;
}