#include "BiddingFacility.h"

const std::vector<const BidSubmission&>* BiddingFacility::finalize()
{
	if (*finalized)
		return finalizedBidList;

	std::vector<const BidSubmission&>* bidList = new std::vector<const BidSubmission&>();
	bidList->reserve(bids->size());
	for (auto kv_bid : *bids)
	{
		bidList->push_back(kv_bid.second);
	}

	return finalizedBidList;
}

BiddingFacility::BiddingFacility()
{
	bids = new std::unordered_map<std::string, BidSubmission&>;
	*finalized = false;
}
BiddingFacility::~BiddingFacility()
{
	delete bids;
	delete finalizedBidList;
	delete finalized;
}


const BidSubmission& BiddingFacility::getWinningBid()
{
	if (!finalized)
		throw "I don't know how to throw exceptions yet.";
	return bids->at(*winningPlayerID);
}



void BiddingFacility::trySubmitBid(const BidSubmission& bid)
{
	if (*finalized)
		return;

	std::pair<std::string,const BidSubmission&> bidMapEntry(bid.getPlayerID(), bid);
	bids->emplace(bidMapEntry);
}

const std::vector <const BidSubmission&>* BiddingFacility::getAllBids() {
	return this->finalize();
}

int BiddingFacility::getNumBids() const
{
	return bids->size();
}

