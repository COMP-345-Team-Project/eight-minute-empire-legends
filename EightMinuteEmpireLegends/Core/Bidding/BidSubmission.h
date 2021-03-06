#pragma once
#include "../pch.h"

struct BidSubmission
{
	BidSubmission(
		std::string playerID,
		std::string playerLastName,
		unsigned int bid
	) :
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
	int getBidAmount() const {
		return bid;
	}
private:
	std::string playerID;
	std::string playerLastName;
	unsigned int bid;
};