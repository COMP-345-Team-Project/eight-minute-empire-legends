#include "../pch.h"
#include "GameEnginePrompts.h"
#include "../GameCore/GameBuilderException.h"
#include "../GameCore/GameBuilder.h"


GameMode GameEnginePrompts::forGameMode()
{
	GameMode gameMode;
	char modeSelected = false;
	while (!modeSelected)
	{
		char tournyOrSingle;
		std::cout << "Please select either (T)ournament or (S)ingle game: ";
		std::cin >> tournyOrSingle;

		if (tournyOrSingle > 96) { tournyOrSingle -= 32; }
		switch (tournyOrSingle)
		{
		case 'T':
			gameMode = GameMode::TOURNAMENT;
			modeSelected = true;
			break;
		case 'S':
			gameMode = GameMode::SINGLE_GAME;
			modeSelected = true;
			break;
		default:
			std::cout << "Please enter 'T' or 'S' as prompted." << std::endl;
			break;
		}
	}
	return gameMode;
}

std::string GameEnginePrompts::forMapFilename()
{
	std::vector<filesystem::path> maps = fetchMapFiles(_mapDir);
	std::vector<std::string> names{};
	std::cout << "Please select a map.\n" << std::endl;
	int index = 0;
	int mapSelection;


	// Map selection
	for (const auto& entry : maps) {
		std::cout << index << ") " << entry.filename() << std::endl;
		index++;
	}
	std::cout << "Enter selection here: ";
	std::cin >> mapSelection;
	if (mapSelection < 0 || mapSelection >= maps.size()) {
		throw GameBuilderException("ERR: Selection index out of range.");
	}
	return maps.at(mapSelection).u8string();
}

int GameEnginePrompts::forNumPlayers()
{
	// Player selection
	int numPlayers;
	bool validNum = false;
	while (!validNum) {
		std::cout << "Please enter the number of players (2-4) : ";
		std::cin >> numPlayers;
		if (cin.fail()) {
			cin.clear();
			cin.sync();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input. Please enter an integer.\n" << std::endl;
		}
		else if (numPlayers < 2 || numPlayers > 4) {
			std::cout << "Player count selection out of range.\n" << std::endl;
		}
		else {
			validNum = true;
		}
	}
	return numPlayers;
}

PlayerContext GameEnginePrompts::forPlayerContext()
{
	PlayerContext playerContext;
	std::cout << "\n------ New player setup ------";
	std::cout << "\nEnter player's last name: ";
	std::cin >> playerContext.lastName;
	std::cout << "Choose player strategy." << std::endl;
	std::cout << "1) Human \n2) Greedy NPC \n3) Moderate NPC" << std::endl;
	std::cout << "Enter choice here: ";
	int stratChoice;
	std::cin >> stratChoice;
	switch (stratChoice)
	{
	case 1:
		playerContext.strategy = PlayerType::HUMAN;
		break;
	case 2:
		playerContext.strategy = PlayerType::NPC_GREEDY;
		break;
	case 3:
		playerContext.strategy = PlayerType::NPC_MODERATE;
		break;
	default:
		std::cout << "Please read next time...\nDefaulting to Moderate NPC.";
		playerContext.strategy = PlayerType::NPC_MODERATE;
		break;
	}
	return playerContext;
}
