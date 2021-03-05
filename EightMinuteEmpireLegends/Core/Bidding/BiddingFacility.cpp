#include "BiddingFacility.h"

std::shared_ptr<std::vector <BidSubmission>> BiddingFacility::generateBidList() {

	std::shared_ptr<std::vector <BidSubmission>> bidList(
		new std::vector<BidSubmission>());

	bidList->reserve(bids->size());
	for (auto kv_bid : *bids)
	{
		bidList->push_back(kv_bid.second);
	}

	return bidList;
}

void BiddingFacility::finalize()
{
	if (isFinalized())
		return;

	// Determine winner, and set winningPlayerID
	if (getNumBids() < 1)
		throw "I dunno how to throw errors yet.";

	winningPlayerID = tieBreaker->ComputeWinner(*generateBidList().get());
	return;
}

BiddingFacility::BiddingFacility(const BidTieBreaker& tieBreaker)
{
	this->tieBreaker = &tieBreaker;
	bids = new std::unordered_map<std::string, BidSubmission>;
}
BiddingFacility::~BiddingFacility()
{
	delete bids;
}

bool BiddingFacility::isFinalized() {
	return winningPlayerID.size() < 1 ? false : true;
}


BidSubmission BiddingFacility::getWinningBid()
{
	if (!isFinalized())
		finalize();
	return bids->at(winningPlayerID);
}



void BiddingFacility::trySubmitBid(const BidSubmission& bid)
{
	if (isFinalized())
		return;

	std::pair<std::string,BidSubmission> bidMapEntry(bid.getPlayerID(), bid);
	bids->emplace(bidMapEntry);
}

std::shared_ptr<std::vector <BidSubmission>> BiddingFacility::getAllBids() {
	if (!isFinalized()) 
		this->finalize();
	return generateBidList();
}

unsigned long long BiddingFacility::getNumBids() const
{
	return bids->size();
}

