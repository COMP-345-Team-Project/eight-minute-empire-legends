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

int AssignmentTwoDriver::RunA2MainLoopDriver()
{
	A2MainLoop a2MainLoop;
	a2MainLoop.Test();

	return 0;
}