#include "../pch.h"
#include "PlayerScore.h"

PlayerScore::PlayerScore() {
	territoryScore = 0;
	continentScore = 0;
	abilityScore = 0;
	elixirScore = 0;
}

PlayerScore& PlayerScore::operator =(const PlayerScore& p) {
	PlayerScore playerScore(p);
	return playerScore;
}

PlayerScore::~PlayerScore() {}

PlayerScore::PlayerScore(const PlayerScore& playerScore) {
	this->territoryScore = playerScore.territoryScore;
	this->ownedTerritories = playerScore.ownedTerritories;

	this->continentScore = playerScore.continentScore;
	this->ownedContinents = playerScore.ownedContinents;

	this->abilityScore = playerScore.abilityScore;
	this->abilities = playerScore.abilities;

	this->elixirScore = playerScore.elixirScore;
}

void PlayerScore::clearScores() {
	territoryScore = 0;
	ownedTerritories.clear();

	continentScore = 0;
	ownedContinents.clear();

	abilityScore = 0;
	abilities.clear();

	elixirScore = 0;
}

void PlayerScore::addOwnedTerritories(std::string territory) {
	territoryScore++;
	ownedTerritories.push_back(territory);
}

void PlayerScore::addOwnedContinents(std::string continent) {
	continentScore++;
	ownedContinents.push_back(continent);
}

void PlayerScore::setElixirScore(int elixirScore) {
	this->elixirScore = elixirScore;
}

void PlayerScore::addAbility(std::string ability) {
	abilities.push_back(ability);
}

void PlayerScore::setAbilityScore(int score) {
	abilityScore = score;
}

int PlayerScore::getTerritoryScore() {
	return territoryScore;
}

int PlayerScore::getContinentScore() {
	return continentScore;
}

int PlayerScore::getElixirScore() {
	return elixirScore;
}

int PlayerScore::getAbilityScore() {
	return abilityScore;
}

int PlayerScore::getTotalScore() {
	return territoryScore + continentScore + elixirScore + abilityScore;
}

std::vector<std::string> PlayerScore::getOwnedTerritories() {
	return ownedTerritories;
}

std::vector<std::string> PlayerScore::getOwnedContinents() {
	return ownedContinents;
}

std::vector<std::string> PlayerScore::getAbilities() {
	return abilities;
}
