#pragma once

#include "PlayerTests.h"

#include "../../Core/Player/Player.h"
#include "../../Core/GameCore/GameCore.h"
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
	altPlayerName = "player2";
	//Temporary fix for the running directory issue, will be removed after
	mapPath = "../Tests/MapLoaderTests/Resources/validJson_validMap.json";
}

int PlayerTests::Test_PlaceArmies()
{	
	std::cout << "\nTesting Player::PlaceArmies()" << std::endl;
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
	std::cout << "Testing the correct use case..." << std::endl;
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

	std::cout << "All test cases passed..." << std::endl;

	return 0;
}

int PlayerTests::Test_MoveArmies() {
	std::cout << "\nTesting Player::MoveArmies()" << std::endl;
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

	std::cout << "All test cases passed..." << std::endl;

	return 0;
}

int PlayerTests::Test_DestroyArmies() {
	std::cout << "\nTesting Player::DestroyArmy()" << std::endl;
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

	std::cout << "All test cases passed..." << std::endl;

	return 0;
}

int PlayerTests::Test_PlaceCities() {
	std::cout << "\nTesting Player::DestroyArmy()" << std::endl;
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

	std::cout << "All test cases passed..." << std::endl;

	return 0;
}

int PlayerTests::Test_PayCoin() {
	std::cout << "\nTesting Player::PayCoin()" << std::endl;
	BidTieBreakerByLastName bidTieBreakerByLastName;
	BiddingFacility* biddingFacility = new BiddingFacility(bidTieBreakerByLastName);
	Player* p1 = new Player(playerName, biddingFacility);
	Player* p2 = new Player(altPlayerName, biddingFacility);
	p1->InitResources(numOfCoins, numOfArmies, numOfCities); //Initial amount is 11

	//Try to pay an amount that is over the initial amount 
	bool errorCaught = false;
	try {
		p1->PayCoin(100);
	}
	catch (PlayerActionException& ex) {
		errorCaught = true;
		std::cout << ex.what() << std::endl;
	}

	//Assert that afterwards the remaining number of coins is correct
	std::cout << "Testing the correct use case..." << std::endl;
	p1->PayCoin(5);
	assert(p1->getCoins() == 6);

	std::cout << "All test cases passed..." << std::endl;

	return 0;
}

int PlayerTests::Test_ComputeScore() {
	std::cout << "\nTesting Player::ComputeScore()" << std::endl;

	//Create maps and players
	Map* map = MapLoader::parseMap(mapPath);
	BidTieBreakerByLastName bidTieBreakerByLastName;
	BiddingFacility* biddingFacility = new BiddingFacility(bidTieBreakerByLastName);
	Player* p1 = new Player(playerName, biddingFacility);
	Player* p2 = new Player(altPlayerName, biddingFacility);
	p1->InitResources(numOfCoins, numOfArmies, numOfCities);
	p2->InitResources(numOfCoins, numOfArmies, numOfCities);

	//Set the starting region
	//Regions from Continent 1
	Vertex* v0 = findVertexById(map, "0");
	Vertex* v1 = findVertexById(map, "1");
	Vertex* v2 = findVertexById(map, "2");
	Vertex* v3 = findVertexById(map, "3");
	Vertex* v4 = findVertexById(map, "4");
	Vertex* v5 = findVertexById(map, "5"); //tie region
	//Regions from Continent 2
	Vertex* v6 = findVertexById(map, "6");
	Vertex* v7 = findVertexById(map, "7");
	//Regions from Continent 3
	Vertex* v10 = findVertexById(map, "10");
	Vertex* v11 = findVertexById(map, "11");
	//Regions from Continent 4, tie continent
	Vertex* v13 = findVertexById(map, "13");
	Vertex* v14 = findVertexById(map, "14");
	//map->setStartingRegion(v1);

	//Assign some regions to the players directly (bypassing Place armies to avoid game logic)
	//p1 owns 3 regions from continent 1, 2 from continent 2, 1 from continent 4 => Owns 2 continent
	v0->getTerritory()->setArmiesByPlayer(1, p1->getPlayerName());
	v1->getTerritory()->setArmiesByPlayer(1, p1->getPlayerName());
	v2->getTerritory()->setArmiesByPlayer(2, p1->getPlayerName());
	v5->getTerritory()->setArmiesByPlayer(1, p1->getPlayerName());
	v6->getTerritory()->setArmiesByPlayer(1, p1->getPlayerName());
	v7->getTerritory()->setArmiesByPlayer(1, p1->getPlayerName());
	v13->getTerritory()->setArmiesByPlayer(1, p1->getPlayerName());

	//p2 owns 2 regions from continent 1, 2 from continent 3, 1 from continent 4 => Owns 1 continent
	v2->getTerritory()->setArmiesByPlayer(1, p2->getPlayerName());
	v3->getTerritory()->setArmiesByPlayer(1, p2->getPlayerName());
	v4->getTerritory()->setArmiesByPlayer(1, p2->getPlayerName());
	v5->getTerritory()->setArmiesByPlayer(1, p2->getPlayerName());
	v10->getTerritory()->setArmiesByPlayer(1, p2->getPlayerName());
	v11->getTerritory()->setArmiesByPlayer(1, p2->getPlayerName());
	v14->getTerritory()->setArmiesByPlayer(1, p2->getPlayerName());

	//Add the deployed armies to the player list of deployed regions
	p1->AddDeployedVertex(v0);
	p1->AddDeployedVertex(v1);
	p1->AddDeployedVertex(v2);
	p1->AddDeployedVertex(v5);
	p1->AddDeployedVertex(v6);
	p1->AddDeployedVertex(v7);
	p1->AddDeployedVertex(v13);
	p2->AddDeployedVertex(v2);
	p2->AddDeployedVertex(v3);
	p2->AddDeployedVertex(v4);
	p2->AddDeployedVertex(v5);
	p2->AddDeployedVertex(v10);
	p2->AddDeployedVertex(v11);

	//Setting up the cards for player 1: 4 ancient cards, 3 nobel cards
	Card* card1 = new Card("Ancient Phoenix", 0, 5, 0, 0, "moveArmy", "", false, 0, 0, true, 0, 0, "");
	Card* card2 = new Card("Ancient Sage", 0, 3, 0, 0, "moveArmy", "", false, 0, 0, false, 0, 0, "1VPperAncient");
	Card* card3 = new Card("Ancient Tree Spirit", 4, 0, 0, 0, "newArmy", "", false, 0, 0, false, 3, 0, "");
	Card* card4 = new Card("Ancient Woods", 1, 0, 1, 0, "buildCity", "newArmy", true, 0, 1, false, 0, 0, "");
	Card* card5 = new Card("Noble Hills", 3, 0, 0, 0, "newArmy", "", false, 0, 0, false, 0, 0, "3NobleCards=4VP");
	Card* card6 = new Card("Noble Knight", 4, 0, 0, 1, "newArmy", "destroyArmy", true, 1, 0, false, 0, 0, "");
	Card* card7 = new Card("Noble Unicorn", 1, 4, 0, 0, "moveArmy", "newArmy", true, 1, 0, false, 0, 0, "");

	p1->addCard(card1);
	p1->addCard(card2);
	p1->addCard(card3);
	p1->addCard(card4);
	p1->addCard(card5);
	p1->addCard(card6);
	p1->addCard(card7);

	p1->addElixirs(card3->getElixer()); //Cards 3 has 3 elixir

	//Setting up the cards for player 2: 4 ancient cards, 3 nobel cards
	Card* card8 = new Card("Dire Dragon", 3, 0, 0, 1, "newArmy", "destroyArmy", true, 0, 0, true, 0, 0, "");
	Card* card9 = new Card("Dire Eye", 4, 0, 0, 0, "newArmy", "", false, 0, 0, true, 0, 0, "");
	Card* card10 = new Card("Dire Giant", 3, 0, 0, 1, "newArmy", "destroyArmy", true, 0, 0, false, 0, 0, "immuneToAttack");
	Card* card11 = new Card("Dire Goblin", 0, 5, 0, 0, "moveArmy", "", false, 0, 0, false, 1, 0, "");
	Card* card12 = new Card("Dire Ogre", 0, 2, 0, 0, "moveArmy", "", false, 0, 0, false, 0, 0, "1VPper3Coins");
	Card* card13 = new Card("Stronghold", 0, 0, 1, 0, "buildCity", "", false, 0, 0, false, 0, 0, "1VPperDireCard");

	p2->addCard(card8);
	p2->addCard(card9);
	p2->addCard(card10);
	p2->addCard(card11);
	p2->addCard(card12);
	p2->addCard(card13);

	p2->addElixirs(card11->getElixer()); //Cards 11 has 1 elixir

	//Validate the compute score based on territories owned
	std::cout << "Asserting the scores return by the functions..." << std::endl;
	assert(p1->ComputeTerritoryScore() == 6);
	assert(p2->ComputeTerritoryScore() == 4);

	//Validate the compute score based on continents owned
	assert(p1->ComputeRegionalScore(map) == 2);
	assert(p2->ComputeRegionalScore(map) == 1);

	//Validate the points based of card abilities
	assert(p1->ComputeAbilityScore() == 8);
	assert(p2->ComputeAbilityScore() == 8);

	//Validate the points based on the number of elixirs
	vector<Player*> players{ p1, p2 };
	assert(p1->ComputeElixirScore(players) == 2);
	assert(p2->ComputeElixirScore(players) == 0);

	//Finally we check the overall compute score function
	assert(p1->ComputeScore(map, players) == 18);
	assert(p2->ComputeScore(map, players) == 13);

	Game testGame;
	testGame.endGame(map, players);

	delete biddingFacility;
	delete p1;
	delete map;

	std::cout << "All test cases passed..." << std::endl;

	return 0;
}