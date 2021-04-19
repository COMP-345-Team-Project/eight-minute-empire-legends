#pragma once
#include "../pch.h"
#include "GameEngine.h"
#include "../GameCore/GameBuilder.h"
#include "../GameCore/GameCore.h"
#include "../GameCore/GameReport.h"
#include "GameContext.h"
#include "PlayerContext.h"
#include "PlayerType.h"
#include "GameEnginePrompts.h"

GameEngine::GameEngine()
{
}

GameContext GameEngine::BuildGameContextInteractively()
{
	std::cout << " _____ _       _     _             ___  ____             _                     " << std::endl;
	std::cout << "|  ___(_)     | |   | |            |  \\/  (_)           | |                    " << std::endl;
	std::cout << "| |__  _  __ _| |__ | |_   ______  | .  . |_ _ __  _   _| |_ ___               " << std::endl;
	std::cout << "|  __|| |/ _` | '_ \\| __| |______| | |\\/| | | '_ \\| | | | __/ _ \\              " << std::endl;
	std::cout << "| |___| | (_| | | | | |_           | |  | | | | | | |_| | ||  __/              " << std::endl;
	std::cout << "\\____/|_|\\__, |_| |_|\\__|          \\_|  |_/_|_| |_|\\__,_|\\__\\___|              " << std::endl;
	std::cout << "          __/ |                                                                " << std::endl;
	std::cout << "         |___/                                                                 " << std::endl;
	std::cout << " _____                _                 _                               _      " << std::endl;
	std::cout << "|  ___|              (_)           _   | |                             | |     " << std::endl;
	std::cout << "| |__ _ __ ___  _ __  _ _ __ ___  (_)  | |     ___  __ _  ___ _ __   __| |___  " << std::endl;
	std::cout << "|  __| '_ ` _ \\| '_ \\| | '__/ _ \\      | |    / _ \\/ _` |/ _ \\ '_ \\ / _` / __| " << std::endl;
	std::cout << "| |__| | | | | | |_) | | | |  __/  _   | |___|  __/ (_| |  __/ | | | (_| \\__ \\ " << std::endl;
	std::cout << "\\____/_| |_| |_| .__/|_|_|  \\___| (_)  \\_____/\\___|\\__, |\\___|_| |_|\\__,_|___/ " << std::endl;
	std::cout << "               | |                                  __/ |                      " << std::endl;
	std::cout << "               |_|                                 |___/                       " << std::endl;
	std::cout << std::endl;
	
	GameContext gameContext;
	gameContext.gameMode = GameEnginePrompts::forGameMode();
	gameContext.mapFilePath = GameEnginePrompts::forMapFilename();
	int numPlayers = GameEnginePrompts::forNumPlayers();
	for (int i = 0; i < numPlayers; i++) {
		gameContext.playerSettings.push_back(
			GameEnginePrompts::forPlayerContext()
		);
	}
	return gameContext;
}


std::vector<GameReport> GameEngine::RunGame(GameContext gameContext)
{
	vector<std::string> names;
	// START - Ensure unique last names
	std::string plName;
	bool validName;
	for (int i = 0; i < gameContext.playerSettings.size(); i++) {
		validName = false;
		while (!validName) {
			plName = gameContext.playerSettings.at(i).lastName;
			if (std::find(names.begin(), names.end(), plName) != names.end()) {
				gameContext.playerSettings.at(i).lastName = gameContext.playerSettings.at(i).lastName + "_";
			}
			else {
				validName = true;
			}
		}
		names.push_back(plName);
	}
	// END - Ensure unique last names

	int numGames = 1;
	if (gameContext.gameMode == GameMode::TOURNAMENT) {
		numGames = 3;
	}
	std::vector<GameReport> gameReports;

	for (int i = 0; i < numGames; i++) {
		Game* game = GameBuilder::build(
			gameContext.playerSettings.size(),
			names,
			gameContext.mapFilePath,
			_configPath
		);
		std::vector<Player*> players = game->getPlayers();
		for (int i = 0; i < players.size(); i++) {
			switch (gameContext.playerSettings[i].strategy)
			{
			case PlayerType::HUMAN:
				players[i]->setStrategy("Human");
				break;
			case PlayerType::NPC_GREEDY:
				players[i]->setStrategy("GreedyComputer");
				break;
			case PlayerType::NPC_MODERATE:
				players[i]->setStrategy("ModerateComputer");
				break;
			default:
				break;
			}
		}
		if (gameContext.gameMode == GameMode::TOURNAMENT)
		{
			game->setCustomEndGameCardCount(10); // Limit to 20 turns
			game->tournyMode = true;
		}
		game->runSetupPhase();
		game->runRoundsUntilEndGame();
		gameReports.push_back(game->endGame());
	}


	return gameReports;
}

void GameEngine::DisplayGameReport(std::vector<GameReport> gameReports)
{
	GameReport tournyReport;

	for (int i = 0; i < gameReports[0].victoryPoints.size(); i++) {
		tournyReport.cards.push_back(0);
		tournyReport.victoryPoints.push_back(0);
		tournyReport.coins.push_back(0);
	}

	for (GameReport gameReport : gameReports) {
		for (int i = 0; i < gameReport.victoryPoints.size(); i++) {
			tournyReport.cards[i] += gameReport.cards[i];
			tournyReport.victoryPoints[i] += gameReport.victoryPoints[i];
			tournyReport.coins[i] += gameReport.coins[i];
		}
	}

	std::cout << "\n\n+--------------------------------------------------" << std::endl;
	std::cout << "+----------   Game Report   -----------------------" << std::endl;
	std::cout << "+--------------------------------------------------" << std::endl;
	std::cout << "|  Payer #\tCards\tVictory points\tCoins" << std::endl;
	for (int i = 0; i < tournyReport.victoryPoints.size(); i++) {
		std::cout << "|  " << i << "\t\t" <<
			tournyReport.cards.at(i) << "\t" <<
			tournyReport.victoryPoints.at(i) << "\t\t" <<
			tournyReport.coins.at(i) << std::endl;
	}
	std::cout << "+--------------------------------------------------" << std::endl;
}
