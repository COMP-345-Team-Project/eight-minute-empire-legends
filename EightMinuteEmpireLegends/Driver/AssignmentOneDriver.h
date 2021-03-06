#pragma once

#include "../Tests/PlayerTests/PlayerTests.h"
#include "../Tests/BiddingTests/BiddingFacilityTests.h"
#include "../Tests/CardsTests/CardsTests.h"
#include "../Tests/MapLoaderTests/MapLoaderTests.h"
#include "../Tests/MapTests/MapTests.h"
#include "../Tests/MapTests/MapTestUtils.h"

class AssignmentOneDriver
{
public:
	int RunMapDriver();
	int RunMapLoaderDriver();
	int RunCardsDriver();
	int RunPlayerDriver();
	int RunBiddingFacilityDriver();
};