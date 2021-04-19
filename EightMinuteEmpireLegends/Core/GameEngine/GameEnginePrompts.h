#pragma once
#include "GameMode.h"
#include "PlayerContext.h"

class GameEnginePrompts
{
public:
	static GameMode forGameMode();
	static std::string forMapFilename();
	static int forNumPlayers();
	static PlayerContext forPlayerContext();
};
