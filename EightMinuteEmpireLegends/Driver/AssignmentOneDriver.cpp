#pragma once
#include "../Core/pch.h"

#include "../Core/Map/Map.h"
#include "../Core/MapLoader/MapLoader.h"
#include "../Core/Player/Player.h"
#include "../Core/Cards/Cards.h"
#include "../Core/Bidding/BiddingFacility.h"
#include "../Core/Bidding/BidTieBreakerByLastName.h"



#include "../Tests/PlayerTests/PlayerTests.h"
#include "../Tests/BiddingTests/BiddingFacilityTests.h"
#include "../Tests/CardsTests/CardsTests.h"
#include "../Tests/MapLoaderTests/MapLoaderTests.h"
#include "../Tests/MapTests/MapTests.h"
#include "../Tests/MapTests/MapTestUtils.h"

#include "AssignmentOneDriver.h"

int AssignmentOneDriver::RunMapDriver()
{
	MapTests mapTests;
	mapTests.Test_ValidatingInvalidMapConstruction_ReturnsFalse();
	mapTests.Test_ValidatingValidMapConstruction_ReturnsTrue();
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
	return playerTests.Test_PlayerFunctionsExecute();
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
