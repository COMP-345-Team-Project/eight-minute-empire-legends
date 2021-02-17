#pragma once
#include "BidSubmission.h"
#include <vector>
#include <memory>

class BidTieBreaker {
public:
	virtual std::shared_ptr<BidSubmission> ComputeWinner(const std::vector<BidSubmission>& bidList) const = 0;
};