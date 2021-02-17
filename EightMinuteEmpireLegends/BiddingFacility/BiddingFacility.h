#pragma once
#include <string>
#include <vector>
#include <unordered_map>

struct BidSubmission
{
	BidSubmission(
		std::string& playerID,
		std::string& playerLastName,
		int& bid
	):
		playerID(playerID),
		playerLastName(playerLastName),
		bid(bid)
	{}
	std::string getPlayerID() const {
		return playerID;
	}
	std::string getPlayerLastName() const {
		return playerLastName;
	}
	int getBidAmount () const {
		return bid;
	}
	private:
	std::string playerID;
	std::string playerLastName;
	int bid;
};

class BiddingFacility
{
private:
	std::unordered_map<std::string, BidSubmission&> * bids;
	std::vector<const BidSubmission&> * finalizedBidList;
	std::string * winningPlayerID;
	bool * finalized;
	const std::vector<const BidSubmission&>* finalize();

public:
	BiddingFacility();
	~BiddingFacility();
	void trySubmitBid(const BidSubmission& bid);
	const BidSubmission& getWinningBid();
	int getNumBids() const;
	const std::vector <const BidSubmission&>* getAllBids();
	const BidSubmission& getBid(std::string playerId);
};