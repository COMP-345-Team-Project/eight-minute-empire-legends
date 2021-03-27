#pragma once

#include "../../Core/Player/Player.h"
#include "../../Core/Bidding/BidTieBreakerByLastName.h"

class PlayerTests
{
public:
	PlayerTests();
	int Test_PlaceArmies();
	int Test_MoveArmies();
	int Test_DestroyArmies();
	int Test_PlaceCities();
	int Test_ComputeScore();
	int Test_PayCoin();

private:
	int numOfArmiesToDeploy;
	int badNumOfArmiesToDeploy;
	int numOfCoins;
	int numOfArmies;
	int numOfCities;
	string playerName;
	string altPlayerName;
	string mapPath;
};