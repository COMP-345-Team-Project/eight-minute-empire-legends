#pragma once

#include "AssignmentOneDriver.h"

#include "../Tests/PlayerTests/PlayerTests.h"
#include "../Tests/BiddingTests/BiddingFacilityTests.h"
#include "../Tests/CardsTests/CardsTests.h"
#include "../Tests/MapLoaderTests/MapLoaderTests.h"
#include "../Tests/MapTests/MapTests.h"
#include "../Tests/MapTests/MapTestUtils.h"

int AssignmentOneDriver::RunMapDriver()
{
	MapTests mapTests;
	mapTests.Test_ValidatingInvalidMapConstruction_ReturnsFalse();
	mapTests.Test_ValidatingValidMapConstruction_ReturnsTrue();
	return 0;
}

int AssignmentOneDriver::RunMapLoaderDriver()
{
	MapLoaderTests mapLoaderTests;
	mapLoaderTests.Test_LoadIncorrectFileFormat_ReturnsNullPointer();
	mapLoaderTests.Test_LoadJsonDisconnectedGraph_WhatShouldHappen();
	mapLoaderTests.Test_LoadJsonMissingContinents_WhatShouldHappen();
	mapLoaderTests.Test_LoadJsonMissingVertices_WhatShouldHappen();
	mapLoaderTests.Test_LoadJsonWrongDataType_WhatShouldHappen();
	mapLoaderTests.Test_LoadValidMap2_Successful();
	mapLoaderTests.Test_LoadValidMap_Successful();
	return 0;
}

int AssignmentOneDriver::RunCardsDriver()
{
	CardsTests cardsTests;
	return cardsTests.Test_CanBuildDeckAndHand_Demo();
}

int AssignmentOneDriver::RunPlayerDriver()
{
	PlayerTests playerTests;
	playerTests.Test_PlaceArmies();
	playerTests.Test_MoveArmies();
	playerTests.Test_DestroyArmies();
	playerTests.Test_PlaceCities();
	return 0;
}

int AssignmentOneDriver::RunBiddingFacilityDriver()
{
	BiddingFacilityTests biddingFacilityTests;
	int passes = 0;
	passes += biddingFacilityTests.Test_PlayerWithMostCoinsWins();
	passes += biddingFacilityTests.Test_PlayerWithAlphabeticallyFirstLastNameWins_WhenBidsAreTied();
	passes += biddingFacilityTests.Test_PlayerWithAlphabeticallyFirstLastNameWins_WhenBidsAreZero();
	return passes;
}
