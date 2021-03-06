#pragma once
#include "../pch.h"

#include "BidTieBreakerByLastName.h"

std::string BidTieBreakerByLastName::ComputeWinner(const std::vector<BidSubmission>& bidList) const
{
	int highestBidValue = 0;
	for (int i = 0; i < bidList.size(); i++) {
		if (bidList[i].getBidAmount() > highestBidValue)
			highestBidValue = bidList[i].getBidAmount();
	}
	std::vector<const BidSubmission*> winningBids;
	for (int i = 0; i < bidList.size(); i++) {
		if (bidList[i].getBidAmount() == highestBidValue)
			winningBids.push_back(&(bidList[i]));
	}

	if (winningBids.size() == 1)
		return winningBids[0]->getPlayerID();

	std::string alphabeticallyFirstLastName = winningBids[0]->getPlayerLastName();
	std::string winningPlayerID = winningBids[0]->getPlayerID();
	for (int i = 1; i < winningBids.size(); i++) {
		std::string currentName = winningBids[i]->getPlayerLastName();
		if (currentName < alphabeticallyFirstLastName)
		{
			alphabeticallyFirstLastName = currentName;
			winningPlayerID = winningBids[i]->getPlayerID();
		}
	}
	return winningPlayerID;
}
