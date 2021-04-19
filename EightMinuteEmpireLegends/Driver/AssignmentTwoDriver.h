#pragma once

#include "../Tests/GameStartTests/GameStartTests.h"
#include "../Tests/PlayerTests/PlayerTests.h"

class AssignmentTwoDriver
{
public:
	int RunGame();
	int RunGameStartDriver();
	int RunSetupPhaseAndMainLoopDriver();
	int RunPlayerDriver();
	int RunComputeScoreTest();
	int RunGameStatisticsTests();
};

