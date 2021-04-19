#pragma once
#include "GameMode.h"
#include "PlayerContext.h"

struct GameContext
{
	GameMode gameMode;
	std::string mapFilePath;
	std::vector<PlayerContext> playerSettings;
};

