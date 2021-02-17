#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

#include "BidSubmission.h"
#include "BidTieBreaker.h"

class BiddingFacility
{
private:
	std::unordered_map<std::string, BidSubmission> * bids;
	std::string winningPlayerID;
	const BidTieBreaker * tieBreaker;
	std::shared_ptr<std::vector <BidSubmission>> generateBidList();
	void finalize();

public:
	BiddingFacility(const BidTieBreaker& tieBreaker);
	BiddingFacility(const BiddingFacility* biddingFacility) = delete;
	~BiddingFacility();
	bool isFinalized();
	void trySubmitBid(const BidSubmission& bid);
	BidSubmission getWinningBid();
	unsigned long long getNumBids() const;
	std::shared_ptr<std::vector <BidSubmission>> getAllBids();
	BidSubmission getBid(const std::string& playerId);
};