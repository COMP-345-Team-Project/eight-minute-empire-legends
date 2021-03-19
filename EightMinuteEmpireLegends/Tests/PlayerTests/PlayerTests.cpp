#pragma once

#include "PlayerTests.h"

#include "../../Core/Player/Player.h"
#include "../../Core/Bidding/BidTieBreakerByLastName.h"
#include "../../Core/MapLoader/MapLoader.h"

int PlayerTests::Test_PlayerFunctionsExecute()
{
	/*Deck deck(2);
	BidTieBreakerByLastName bidTieBreakerByLastName;
	Player* p1 = new Player("player1", deck, bidTieBreakerByLastName);

	/*p1->BuildCity();
	p1->DestroyArmy();
	p1->MoveArmies();
	p1->MoveOverLand();
	p1->payCoin();
	p1->PlaceNewArmies();*/

	delete p1;*/
	return 0;
}

Vertex* findVertexById(Map* map, string id) {
	auto it = find_if(map->vertices().begin(), map->vertices().end(), [&id](Vertex* vertexPtr) {return vertexPtr->getId().compare(id) == 0; });

	if (it != map->vertices().end())
	{
		return *it;
	}
}


int PlayerTests::Test_PlayerComputeScoreFunctionsExecute() {
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

	/*p1->BuildCity();
	p1->DestroyArmy();
	p1->MoveArmies();
	p1->MoveOverLand();
	p1->payCoin();
	p1->PlaceNewArmies();*/

	delete p1;
	delete p2;
	delete map;
	return 0;
}