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
	graphSymbols = new char[this->maxNumOfPlayer]{ '*', '-', '%', '@' };
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
	std::cout << "\n***************************Updating Statistics***************************" << std::endl;
	//Pull the data from the model
	refreshData();

	//Print out the player stats
	vector<Player*> players = gameModel->getPlayers();

	std::cout << "---------------------Player stats---------------------" << std::endl;
	for (int i = 0; i < players.size(); i++) {
		if (!players[i]->isNeutralPlayer()) {
			printPlayerStats(players[i]);
		}
	}

	//Print the bar graph
	std::cout << "---------------------Procession chart---------------------" << std::endl;
	generateStatsTable();
	std::cout << "\n*************************************************************************" << std::endl;
}

void GameStatistics::printPlayerStats(Player* player) {
	std::cout << "******Player: " << player->getPlayerName() << "******" << std::endl;
	std::cout << "Available coins: " << player->getCoins() << std::endl;
	std::cout << "Available armies: " << player->getAvailableArmies() << std::endl;
	std::cout << "Available cities: " << player->getAvailableCities() << std::endl;
	std::cout << "Total cards owned: " << player->getCards().size() << std::endl;

	PlayerScore playerScore = player->getPlayerScore();
	std::cout << "Number of owned regions: " << playerScore.getTerritoryScore() << std::endl;
	std::cout << "Currently owned regions: ";
	printVector(playerScore.getOwnedTerritories());
	std::cout << std::endl;
	std::cout << "Number of owned continents: " << playerScore.getContinentScore() << std::endl;
	std::cout << "Currently owned continents: ";
	printVector(playerScore.getOwnedContinents());
	std::cout << std::endl;
	std::cout << "Abilities: ";
	printVector(playerScore.getAbilities());
	std::cout << std::endl;
	std::cout << "Elixir points: " << playerScore.getElixirScore() << std::endl;
	std::cout << "Total score: " << playerScore.getTotalScore() << std::endl;
	std::cout << std::endl;
}

void GameStatistics::generateStatsTable() {
	int numOfPlayers = gameModel->getPlayers().size();

	//Generates the bars
	printCategory("Territories", territoryScores, numOfPlayers);
	printCategory("Continents", continentScores, numOfPlayers);
	printCategory("Cities\t", builtCitiesCount, numOfPlayers);

	//Generate the x axis
	std::cout << "\t\t0----5----10----15----20----25----30" << std::endl;

	//Name of graph
	std::cout << "Summary of number of territories/continents/cities owned by each player" << std::endl;

	std::cout << std::endl;
	std::cout << "Lengends:" << std::endl;

	for (int i = 0; i < numOfPlayers; i++) {
		std::cout << gameModel->getPlayers()[i]->getPlayerName() << ": " << graphSymbols[i] << std::endl;
	}
}

void GameStatistics::printVector(vector<std::string> data) {
	for (int i = 0; i < data.size(); i++) {
		std::cout << data[i] << "; ";
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
			//cout << "*";
		}

		cout << std::endl;
		cout << "\t\t|";
	}

	cout << std::endl;
}
