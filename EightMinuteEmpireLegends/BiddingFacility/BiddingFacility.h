#pragma once
#include <string>
#include <unordered_map>
#include "bid.h"

struct BidSubmission
{
	std::string playerID;
	std::string playerLastName;
	int bid;
};

class BiddingFacility
{
private:
	std::unordered_map<std::string, Bid&> bids;
	bool finalized;
public:
	BiddingFacility();
	void submitBid(BidSubmission& bid);
	Bid getWinner();
	int getNumBids();
	int getPoolSize();
	Bid* getAllBids();
	Bid& getBid(std::string playerId);
	
};