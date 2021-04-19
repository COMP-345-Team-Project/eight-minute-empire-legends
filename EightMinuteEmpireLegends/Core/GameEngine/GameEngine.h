#pragma once
#include "../pch.h"
#include "GameContext.h"
#include "../GameCore/GameReport.h"
#include "PlayerContext.h"

class GameEngine
{
public:
	GameEngine();
	GameContext BuildGameContextInteractively();
	std::vector<GameReport> RunGame(GameContext gameContext);
	void DisplayGameReport(std::vector<GameReport> gameReports);
};