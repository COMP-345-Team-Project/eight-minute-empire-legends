#pragma once

#include "AssignmentTwoDriver.h"

int AssignmentTwoDriver::RunGameStartDriver() 
{
	GameStart gameStartTest;
	gameStartTest.Test_ReadConfigFile();
	gameStartTest.Test_MissingConfigFile();
	gameStartTest.Test_BuildGame();
	return 0;
}