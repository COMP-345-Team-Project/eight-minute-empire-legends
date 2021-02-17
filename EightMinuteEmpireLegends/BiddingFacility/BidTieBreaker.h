#pragma once
#include "BidSubmission.h"
#include <vector>

class BidTieBreaker {
public:
	virtual std::string ComputeWinner(const std::vector<BidSubmission>& bidList) const = 0;
};