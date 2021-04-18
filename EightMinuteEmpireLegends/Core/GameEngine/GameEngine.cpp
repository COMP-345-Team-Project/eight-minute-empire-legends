#include "../pch.h"
#include "GameEngine.h"
#include "../GameCore/GameBuilder.h"
#include "../GameCore/GameCore.h"
#include "../GameCore/GameReport.h"
#include "GameEnginePrompts.h"

GameEngine::GameEngine()
{
}

GameContext GameEngine::BuildGameContextInteractively()
{
	std::cout << " _____ _       _     _             ___  ____             _                     " << std::endl;
	std::cout << "|  ___(_)     | |   | |            |  \/  (_)           | |                    " << std::endl;
	std::cout << "| |__  _  __ _| |__ | |_   ______  | .  . |_ _ __  _   _| |_ ___               " << std::endl;
	std::cout << "|  __|| |/ _` | '_ \| __| |______| | |\/| | | '_ \| | | | __/ _ \              " << std::endl;
	std::cout << "| |___| | (_| | | | | |_           | |  | | | | | | |_| | ||  __/              " << std::endl;
	std::cout << "\____/|_|\__, |_| |_|\__|          \_|  |_/_|_| |_|\__,_|\__\___|              " << std::endl;
	std::cout << "          __/ |                                                                " << std::endl;
	std::cout << "         |___/                                                                 " << std::endl;
	std::cout << " _____                _                 _                               _      " << std::endl;
	std::cout << "|  ___|              (_)           _   | |                             | |     " << std::endl;
	std::cout << "| |__ _ __ ___  _ __  _ _ __ ___  (_)  | |     ___  __ _  ___ _ __   __| |___  " << std::endl;
	std::cout << "|  __| '_ ` _ \| '_ \| | '__/ _ \      | |    / _ \/ _` |/ _ \ '_ \ / _` / __| " << std::endl;
	std::cout << "| |__| | | | | | |_) | | | |  __/  _   | |___|  __/ (_| |  __/ | | | (_| \__ \ " << std::endl;
	std::cout << "\____/_| |_| |_| .__/|_|_|  \___| (_)  \_____/\___|\__, |\___|_| |_|\__,_|___/ " << std::endl;
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
	return GameContext();
}


GameReport GameEngine::RunGame(GameContext gameContext)
{
	vector<std::string> names;
	// START - Ensure unique last names
	std::string plName;
	bool validName;
	for (int i = 0; i < gameContext.playerSettings.size() ; i++) {
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

	Game* game = GameBuilder::build(
		gameContext.playerSettings.size(), 
		names, 
		gameContext.mapFilePath,
		_configPath
	);
	if (gameContext.gameMode == GameMode::TOURNAMENT)
	{
		game->setCustomEndGameCardCount(10); // Limit to 20 turns
	}
	game->runSetupPhase();
	game->runRoundsUntilEndGame();
	game->endGame();

	return GameReport();
}

void GameEngine::DisplayGameReport(GameReport gameReport)
{
}
