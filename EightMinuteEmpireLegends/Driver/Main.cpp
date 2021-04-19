#pragma once

#include "Driver.h"
#include "GameEngine/GameEngine.h"
#include "GameEngine/PlayerContext.h"

int main(int argc, char** argv) 
{
	// TODO: Parse command line arguments and execute corresponding driver with params.

	//Driver driver;
	////driver.RunAssignmentOneDriver();
	//driver.RunAssignmentTwoDriver();
	////driver.RunStrategyDriver();

	GameEngine gameEngine;
	GameContext gameContext = gameEngine.BuildGameContextInteractively();
	std::vector<GameReport> gameReport = gameEngine.RunGame(gameContext);
	gameEngine.DisplayGameReport(gameReport);

	return 0;
}
