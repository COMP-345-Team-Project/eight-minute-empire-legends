#pragma once
#include "GameContext.h"
#include "GameReport.h"

class GameEngine
{
public:
	GameEngine();
	GameContext BuildGameContextInteractively();
	GameReport RunGame(GameContext gameContext);
	void DisplayGameReport(GameReport gameReport);
};

