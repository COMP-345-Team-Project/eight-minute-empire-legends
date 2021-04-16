#pragma once
#include <string>

class GameStatisticsTests
{
public:
	GameStatisticsTests();
	void Test_PrintPlayerStats();
	void Test_Driver();
private:
	int numOfArmiesToDeploy;
	int badNumOfArmiesToDeploy;
	int numOfCoins;
	int numOfArmies;
	int numOfCities;
	std::string playerName;
	std::string altPlayerName;
	std::string mapPath;
}; 
