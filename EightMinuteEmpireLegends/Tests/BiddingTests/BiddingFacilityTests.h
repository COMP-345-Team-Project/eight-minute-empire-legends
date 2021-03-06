#pragma once

#include "../../Core/Bidding/BiddingFacility.h"
#include "../../Core/Bidding/BidTieBreakerByLastName.h"

class BiddingFacilityTests
{
public:
	int Test_PlayerWithMostCoinsWins();
	int Test_PlayerWithAlphabeticallyFirstLastNameWins_WhenBidsAreTied();
	int Test_PlayerWithAlphabeticallyFirstLastNameWins_WhenBidsAreZero();
};