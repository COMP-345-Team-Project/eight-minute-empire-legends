#pragma once

#include "GameTest.h"
#include "../../Core/GameCore/GameCore.h"
#include "../../Core/GameCore/GameBuilder.h"

void GameTest::Test_RunGame() {
	Game* game = GameBuilder::build();
	game->runSetupPhase();
	game->runRoundsUntilEndGame();
	game->endGame();
}