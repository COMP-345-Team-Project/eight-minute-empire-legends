#include <iostream>

//////////////////////////////////////////////////

// TO BE REPLACED WITH ACTUAL MAIN DRIVER.

// PLEASE USE AS REFERENCE FOR INCLUDING
// HEADER FILES FROM OTHER PROJECTS.

// INTER-PROJECT DEPENDENCIES SHOULD
// ARE ALREADY CONFIGURED.

//////////////////////////////////////////////////

#include "../BiddingFacility/BiddingFacility.h"
#include "../BiddingFacility/BidSubmission.h"
#include "../BiddingFacility/BidTieBreakerByLastName.h"

#include "../Player/Player.h"

int main() {

    BidTieBreakerByLastName tieBreaker;

    //----------------------------------------------------------------
    //                        Player Driver 
    //----------------------------------------------------------------

    //assuming 2 player game 
    Deck deck(2);
    Player* p1 = new Player("player1", deck, tieBreaker);

    p1->BuildCity();
    p1->DestroyArmy();
    p1->MoveArmies();
    p1->MoveOverLand();
    p1->payCoin();
    p1->PlaceNewArmies();

    //----------------------------------------------------------------
    //                   BiddingFacility Driver 
    //----------------------------------------------------------------

    /////////////////////////////////////////
    // Test player with most coins wins

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

    std::cout << "Hello World!";
    return 0;
}