#pragma once
#include "../GameCore/GameCore.h"
#include "GameObservers.h"

class GameStatistics : public Observer {
private:
	Game* gameModel;
	int* territoryScores;
	int* continentScores;
	int* builtCitiesCount;
	char* graphSymbols;
	int maxNumOfPlayer;
	void generateStatsTable();
	void printCategory(std::string categoryName, int values[], int size);
	void printVector(vector<std::string> data);
	void printPlayerStats(Player* player);
	void refreshData();
public:
	GameStatistics();
	GameStatistics(Game* game);
	~GameStatistics();

	void update();
};
