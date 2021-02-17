#include <iostream>
#include <string>

#include "BiddingFacility.h"
#include "BidTieBreakerByLastName.h"



int main(int argc, char** argv) {

    BidTieBreakerByLastName tieBreaker;
    BiddingFacility biddingFacility(tieBreaker);

    BidSubmission bidPlayerA(
        "plaserA",
        "playerLastName",
        22
    );
    BidSubmission bidPlayerB(
        "paserB",
        "klfredson",
        21
    );
    BidSubmission bidPlayerC(
        "paserB",
        "balfredson",
        200
    );

    biddingFacility.trySubmitBid(bidPlayerA);
    biddingFacility.trySubmitBid(bidPlayerB);
    biddingFacility.trySubmitBid(bidPlayerC);

    std::cout <<
        biddingFacility.getWinningBid().getPlayerLastName()
        << std::endl;


    return 0;
}