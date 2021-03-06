#pragma once

#include "BiddingFacilityTests.h"
#include "../../Core/Bidding/BiddingFacility.h"
#include "../../Core/Bidding/BidTieBreakerByLastName.h"

int BiddingFacilityTests::Test_PlayerWithMostCoinsWins()
{
    BidTieBreakerByLastName tieBreaker;

    BiddingFacility t1_biddingFacility(tieBreaker);

    BidSubmission t1_bidPlayerA(
        "playerA",
        "aalfredson",
        0
    );
    BidSubmission t1_bidPlayerB(
        "playerB",
        "balfredson",
        3
    );
    BidSubmission t1_bidPlayerC(
        "playerC",
        "calfredson",
        2
    );

    t1_biddingFacility.trySubmitBid(t1_bidPlayerA);
    t1_biddingFacility.trySubmitBid(t1_bidPlayerB);
    t1_biddingFacility.trySubmitBid(t1_bidPlayerC);

    // Assert
    if (t1_biddingFacility.getWinningBid().getPlayerID() != t1_bidPlayerB.getPlayerID())
        return 1;

    return 0;
}

int BiddingFacilityTests::Test_PlayerWithAlphabeticallyFirstLastNameWins_WhenBidsAreTied()
{
    BidTieBreakerByLastName tieBreaker;

    /////////////////////////////////////////
    // Test player alphabetically first last 
    // name wins when bids are tied

    BiddingFacility t2_biddingFacility(tieBreaker);

    BidSubmission t2_bidPlayerA(
        "playerA",
        "aalfredson",
        0
    );
    BidSubmission t2_bidPlayerB(
        "playerB",
        "balfredson",
        3
    );
    BidSubmission t2_bidPlayerC(
        "playerC",
        "calfredson",
        3
    );

    t2_biddingFacility.trySubmitBid(t2_bidPlayerA);
    t2_biddingFacility.trySubmitBid(t2_bidPlayerB);
    t2_biddingFacility.trySubmitBid(t2_bidPlayerC);

    // Assert
    if (t2_biddingFacility.getWinningBid().getPlayerID() != t2_bidPlayerB.getPlayerID())
        return 1;
    return 0;
}

int BiddingFacilityTests::Test_PlayerWithAlphabeticallyFirstLastNameWins_WhenBidsAreZero()
{
    BidTieBreakerByLastName tieBreaker;

    /////////////////////////////////////////
    // Test player alphabetically first last 
    // name wins when bids are zero

    BiddingFacility t3_biddingFacility(tieBreaker);

    BidSubmission t3_bidPlayerA(
        "playerA",
        "aalfredson",
        0
    );
    BidSubmission t3_bidPlayerB(
        "playerB",
        "balfredson",
        0
    );
    BidSubmission t3_bidPlayerC(
        "playerC",
        "calfredson",
        0
    );

    t3_biddingFacility.trySubmitBid(t3_bidPlayerA);
    t3_biddingFacility.trySubmitBid(t3_bidPlayerB);
    t3_biddingFacility.trySubmitBid(t3_bidPlayerC);

    // Assert
    if (t3_biddingFacility.getWinningBid().getPlayerID() != t3_bidPlayerA.getPlayerID())
        return 1;

    return 0;
}
