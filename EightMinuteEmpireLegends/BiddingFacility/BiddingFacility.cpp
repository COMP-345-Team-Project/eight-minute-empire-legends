#include "BiddingFacility.h"

std::shared_ptr<std::vector <BidSubmission>> BiddingFacility::generateBidList() {
	
	std::shared_ptr<std::vector<BidSubmission>> bidList(
		new std::vector<BidSubmission>());

	bidList.get()->reserve(bids->size());
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
	*winningPlayerID = tieBreaker->ComputeWinner(*generateBidList().get())
		.get()->getPlayerID();
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
	delete winningPlayerID;
	delete tieBreaker;
}

bool BiddingFacility::isFinalized() {
	return winningPlayerID == nullptr ? false : true;
}


const BidSubmission& BiddingFacility::getWinningBid()
{
	if (!isFinalized())
		throw "I don't know how to throw exceptions yet.";
	return bids->at(*winningPlayerID);
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
	return generateBidList(); // TODO: Cache bidlist in member variable
}

unsigned long long BiddingFacility::getNumBids() const
{
	return bids->size();
}

