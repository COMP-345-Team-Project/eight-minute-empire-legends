#pragma once
#include <vector>
#include <string>

class PlayerScore {
private:
	int territoryScore;
	std::vector<std::string> ownedTerritories;
	int continentScore;
	std::vector<std::string> ownedContinents;
	int abilityScore;
	std::vector<std::string> abilities;
	int elixirScore;
public:
	PlayerScore();
	PlayerScore(const PlayerScore& playerScore);
	~PlayerScore();
	PlayerScore& operator =(const PlayerScore& p);

	int getTerritoryScore();
	std::vector<std::string> getOwnedTerritories();
	void addOwnedTerritories(std::string territory);

	int getContinentScore();
	std::vector<std::string> getOwnedContinents();
	void addOwnedContinents(std::string territory);

	int getAbilityScore();
	std::vector<std::string> getAbilities();
	void addAbility(std::string ability);
	void setAbilityScore(int score);

	int getElixirScore();
	void setElixirScore(int elixirScore);

	void clearScores();

	//void setOwnedTerritories(std::vector<std::ownedTerritories);

	//void printOwnedTerritories();
	//void printOwnedContinents();
	//void printAbilities();

	int getTotalScore();
};
