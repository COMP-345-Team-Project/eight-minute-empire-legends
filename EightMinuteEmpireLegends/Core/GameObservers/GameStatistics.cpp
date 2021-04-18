#include "GameStatistics.h"

//Game statistics class
GameStatistics::GameStatistics() : Observer() {
};

GameStatistics::GameStatistics(Game* game) : Observer() {
	this->gameModel = game;
	this->gameModel->attach(this);

	//Max number of player per game is 4
	this->maxNumOfPlayer = 4;
	territoryScores = new int[this->maxNumOfPlayer]{ 0, 0, 0, 0 };
	continentScores = new int[this->maxNumOfPlayer]{ 0, 0, 0, 0 };
	builtCitiesCount = new int[this->maxNumOfPlayer]{ 0, 0, 0, 0 };

	//We hard code the symbols
	graphSymbols = new char[this->maxNumOfPlayer]{ '*', '$', '%', '@' };
};

GameStatistics::~GameStatistics() {
	delete territoryScores;
	delete continentScores;
	delete builtCitiesCount;

	//You dont want to delete the game model here!
}

void GameStatistics::refreshData() {
	//The Observer pull the data from the Game model
	vector<Player*> players = gameModel->getPlayers();
	int defaultNumberOfCities = gameModel->getResources()->getAssignedCities();

	for (int i = 0; i < players.size(); i++) {
		if (!players[i]->isNeutralPlayer()) {
			PlayerScore playerScore = players[i]->getPlayerScore();
			territoryScores[i] = playerScore.getTerritoryScore();
			continentScores[i] = playerScore.getContinentScore();
			builtCitiesCount[i] = defaultNumberOfCities - players[i]->getAvailableCities();
		}
	}
}

void GameStatistics::update() {
	vector<Player*> players = gameModel->getPlayers();

	std::cout << "---------------------Player stats---------------------" << std::endl;
	for (int i = 0; i < players.size(); i++) {
		if (!players[i]->isNeutralPlayer()) {
			printPlayerStats(players[i]);
		}
	}

	std::cout << "---------------------Procession chart---------------------" << std::endl;
	generateStatsTable();
}

void GameStatistics::printPlayerStats(Player* player) {
	std::cout << "******Player: " << player->getPlayerName() << "******" << std::endl;
	std::cout << "Available coins: " << player->getCoins() << std::endl;
	std::cout << "Available armies: " << player->getAvailableArmies() << std::endl;
	std::cout << "Available cities: " << player->getAvailableArmies() << std::endl;
	std::cout << "Total cards owned: " << player->getCards().size() << std::endl;

	PlayerScore playerScore = player->getPlayerScore();
	std::cout << "Number of owned regions: " << playerScore.getTerritoryScore() << std::endl;
	std::cout << "Currently owned regions: " << std::endl;
	printVector(playerScore.getOwnedTerritories());
	std::cout << "Number of owned continents: " << playerScore.getContinentScore() << std::endl;
	printVector(playerScore.getOwnedContinents());
	std::cout << "Abilities: " << std::endl;
	printVector(playerScore.getAbilities());
	std::cout << "Elixir points: " << playerScore.getElixirScore() << std::endl;
	std::cout << "Total score: " << playerScore.getTotalScore() << std::endl;
	std::cout << std::endl;
}

void GameStatistics::generateStatsTable() {
	std::cout << "--------------------Summary----------------------" << std::endl;

	int numOfPlayers = gameModel->getPlayers().size();
	printCategory("Owned territories", territoryScores, numOfPlayers);
	printCategory("Owned continents", continentScores, numOfPlayers);
	printCategory("Built cities", builtCitiesCount, numOfPlayers);

	std::cout << "0----5----10----15----20----25----30----35----40----45----50" << std::endl;
	std::cout << std::endl;
	std::cout << "Lengends:" << std::endl;

	for (int i = 0; i < numOfPlayers; i++) {
		std::cout << graphSymbols[i] << ": " << gameModel->getPlayers()[i];
	}
}

void GameStatistics::printVector(vector<std::string> data) {
	for (int i = 0; i < data.size(); i++) {
		std::cout << data[i] << "\t";
	}
}

void GameStatistics::printCategory(std::string categoryName, int values[], int size) {
	//Print the graph
	cout << categoryName << "\t|";

	// i corressponds to the player (For each player)
	for (int i = 0; i < size; i++) {
		// j corresponds to a value of the category
		for (int j = 0; j < values[i]; j++) {
			cout << graphSymbols[i];
		}

		cout << std::endl;
		cout << "\t|";
	}

	cout << std::endl;
}
