#pragma once
#include "../pch.h"

#include "BidTieBreaker.h"

class BidTieBreakerByLastName : public BidTieBreaker
{
public:
	std::string ComputeWinner(const std::vector<BidSubmission>& bidList) const;
};

