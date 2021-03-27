#pragma once

#include "../../Core/pch.h"

class GameStart
{
public:
	int Test_ReadConfigFile_Success();
	int Test_ReadConfigFile_Failure();
	int Test_PlayerInput_SelectPlayerCount_ValidEntry();
	int Test_PlayerInput_SelectPlayerCount_InvalidEntry();
	int Test_PlayerInput_MapSelect_ValidEntry();
	int Test_PlayerInput_MapSelect_InvalidEntry();
	int Test_BuildGame_Success();
	int Test_BuildGame_Failure();
	int Demo_BuildGame();

	void Passed(std::string testName);
};

