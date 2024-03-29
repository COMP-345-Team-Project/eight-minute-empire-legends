 #pragma once

#include "AssignmentTwoDriver.h"

#include "../Tests/GameStartTests/GameStartTests.h"
#include "../Tests/GameTests/GameTest.h";
#include "../Tests/ObserverTests/GameStatisticsTests.h"

int AssignmentTwoDriver::RunGame()
{
	GameTest gameTest;
	gameTest.Test_RunGame();
	return 0;
}

// Part 1: Game start
int AssignmentTwoDriver::RunGameStartDriver() 
{
	GameStart gameStartTest;
	gameStartTest.Test_ReadConfigFile_Failure();
	gameStartTest.Test_BuildGame_Success();
	gameStartTest.Test_BuildGame_Failure();
	gameStartTest.Test_ReadConfigFile_Success();
	gameStartTest.Test_PlayerInput_SelectPlayerCount_ValidEntry();
	gameStartTest.Test_PlayerInput_SelectPlayerCount_InvalidEntry();
	gameStartTest.Test_PlayerInput_MapSelect_ValidEntry();
	gameStartTest.Test_PlayerInput_MapSelect_InvalidEntry();
	gameStartTest.Demo_BuildGame();
	gameStartTest.Demo_DisplayTerritories();
	return 0;
}
#include "../Tests/SetupPhaseTests/SetupPhaseTests.h"

// Part 2: Game play: startup phase
int AssignmentTwoDriver::RunSetupPhaseAndMainLoopDriver()
{
	SetupPhaseTests setupPhaseTests;
	setupPhaseTests.Test_SetupPhaseAndGameLoopExecutes_GivenValidInput();

	//setupPhaseTests.Test_PlaceArmies();
	//setupPhaseTests.Test_MoveArmies();
	//setupPhaseTests.Test_BuildCity();
	//setupPhaseTests.Test_DestroyArmies();
	return 0;
}

// Part 3: Game play: main game loop


// Part 4: Main game loop: The player actions
int AssignmentTwoDriver::RunPlayerDriver()
{
	PlayerTests playerTests;
	playerTests.Test_PlaceArmies();
	playerTests.Test_MoveArmies();
	playerTests.Test_DestroyArmies();
	playerTests.Test_PlaceCities();
	playerTests.Test_PayCoin();
	return 0;
}

// Part 5: Main game loop : after the action


// Part 6: Main game loop : Compute the game score
int AssignmentTwoDriver::RunComputeScoreTest()
{
	PlayerTests playerTests;
	playerTests.Test_ComputeScore();
	return 0;
}

//Observer Tests
int AssignmentTwoDriver::RunGameStatisticsTests() {
	GameStatisticsTests gameStats;
	//gameStats.Test_PrintPlayerStats();
	gameStats.Test_Driver();
	return 0;
}