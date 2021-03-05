#pragma once
#include "../pch.h"

#include "BidSubmission.h"

class BidTieBreaker {
public:
	virtual std::string ComputeWinner(const std::vector<BidSubmission>& bidList) const = 0;
};