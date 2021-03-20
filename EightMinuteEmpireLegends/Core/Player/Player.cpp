#pragma once
#include "../pch.h"
#include "Player.h"
#include "../Cards/Cards.h"

Player::Player(std::string name, Deck deck, BiddingFacility& biddingFacility) : playerName(name), coin(14), hand(deck), biddingFacility(biddingFacility) {}

Player::~Player() {}

int Player::getCoins() {
	return coin;
}

int Player::getAvailableArmies() {
	return availableArmies;
}

int Player::getAvailableCities() {
	return availableCities;
}

vector<Card> Player::getCards() {
	return hand.getCards();
}

std::string Player::getPlayerName() {
	return playerName;
}


void Player::PayCoin(int coins) {
	std::cout << "Entered payCoin method" << std::endl;
}

void Player::PlaceNewArmies(Map* map, Vertex* v, int numOfArmies) {
	//The number of Armies must be more than 0
	if (numOfArmies < 0) {
		std::cout << "Number of armies must be larger than 0" << std::endl;
		return;
	}

	Territory* t = v->getTerritory();
	//You can only place new armies in the starting region or a region you owned with at least 1 city
	if (v != map->getStartingRegion() || !(t->getCitiesByPlayer(playerName) > 0)) { 
		std::cout << "Armies must be built on a starting region, or a region owned by a player wit at least 1 city built" << std::endl;
		return;
	}

	//Update the number of armies and owner
	int newNumOfArmies = t->getArmiesByPlayer(playerName) + numOfArmies;
	t->setArmiesByPlayer(numOfArmies, playerName);
}

void Player::MoveArmies(Map* map, Vertex* from, Vertex* to, int numOfArmies, int& remainingMoves) {
	//We perform some validation before actually moving the armies
	if (from == to) {
		std::cout << "The from and to destination is the same territory." << std::endl;
		return;
	}

	int fromNumOfArmies = from->getTerritory()->getArmiesByPlayer(playerName);
	if (numOfArmies > fromNumOfArmies) {
		std::cout << "The amount of armies moved exceed the number of available armies. Need to move " << numOfArmies << " but only have " << fromNumOfArmies << std::endl;
		return;
	}

	//Make sure that the vertices are adjacent
	vector<Vertex*>::iterator vertexIter;
	vector<Vertex*> adjacentVertices = map->adjacentVertices(from);

	for (vertexIter = adjacentVertices.begin(); vertexIter != adjacentVertices.end(); vertexIter++) {
		//if the 2 vertices are actually adjacent, then we move the armies
		if (*vertexIter == to) {
			//First we calculate the movement cost
			int movementCost = 0;
			if (from->getTerritory()->getContinent().compare(to->getTerritory()->getContinent()) == 0) {
				std::cout << "Moving across land..." << std::endl;
				movementCost = numOfArmies;
			}
			else {
				std::cout << "Moving across water..." << std::endl;
				movementCost = numOfArmies*3;
			}
			
			//If we dont have enough remaining moves
			if (movementCost > remainingMoves) {
				std::cout << "Not enough remaining moves to move the armies, required " << movementCost << " but only have" << remainingMoves << std::endl;
				return;
			}

			//Decrease the cost and move the armies
			remainingMoves -= movementCost;
			from->getTerritory()->destroyArmiesByPlayer(numOfArmies);
			to->getTerritory()->addArmiesByPlayer(numOfArmies);
		}
	}
}

void Player::DestroyArmy(Vertex* v, int numOfArmies) {
	std::cout << "Entered BuildCity method" << std::endl;
}

void Player::BuildCity(Vertex* v, int numOfArmies) {
	std::cout << "Entered BuildCity method" << std::endl;
}

void Player::InitResources(int coin, int armies, int cities) {
	std::cout << "Entered DestroyArmy method" << std::endl;
}

vector<Card> Player::getCards() {
	return hand.getCards();
}
int Player::ComputeScore(Map& map) {
	cout << "Starting score calculation of player " << this->playerName << ": " << endl;

	//Calculating the territories owned by the player
	int ownedTerritoriesScore = this->territories.size();
	cout << "Territories score: " << ownedTerritoriesScore << endl;

	int ownedContinentsScore = ComputeRegionalScore(map);
	cout << "Continents score: " << ownedContinentsScore << endl;

	int abilityScore = ComputeAbilityScore();
	cout << "Ability score: " << abilityScore << endl;

	int total = ownedTerritoriesScore + ownedContinentsScore + abilityScore;
	cout << "Total score: " << total << endl;

	return total;
}

int Player::ComputeTerritoryScore() {
	//The territory score equals to the number of regions owned
	return this->territories.size();
}

int Player::ComputeRegionalScore(Map& map) {
	int continentPoints = 0;

	//Calculating the regional score of all players
	//Initializing the point accumlator to store the points of all players
	std::map<string, std::map<string, int>> pointAccumulator;
	for (int i = 0; i < map.continents().size(); i++) {
		Continent* continent = map.continents().at(i);
		std::map<string, int> playerPointsPerRegion;
		pointAccumulator.insert(pair<string, std::map<string, int>>(continent->name, playerPointsPerRegion));
		continent = NULL;
	}

	//For each vertex (territory) by each player, we add 1 point to that player
	for (int i = 0; i < map.vertices().size(); i++) {
		Vertex* currVertex = map.vertices().at(i);
		Territory* currTerritory = map.vertices().at(i)->getTerritory();
		string owner = currTerritory->getOwner();

		std::map<string, int> continentPoints = pointAccumulator[currTerritory->getName()];

		if (continentPoints.find(owner) == continentPoints.end()) {
			continentPoints.insert(pair<string, int>(owner, 0));
		}

		continentPoints[owner]++;
	}

	//Now we check if this player has the maximum points in each continent
	for (std::map<string, std::map<string, int>>::iterator iter = pointAccumulator.begin(); iter != pointAccumulator.end(); ++iter) {
		if(this->OwnsContinent(iter->second))
			continentPoints++;
	}

	return continentPoints;
}

bool Player::OwnsContinent(std::map<string, int>& continentScores) {
	string owner = "";
	int maxScore = 0;
	bool tied = false;
	
	//Looping through all the scores of all players in a specific continent
	for (std::map<string, int>::const_iterator iter = continentScores.begin(); iter != continentScores.end(); ++iter)
	{
		//If a player has a score higher than the known max score, set the owner to the player and set his score to maxScore
		if (iter->second > maxScore) {
			owner = iter->first;
			maxScore = iter->second;
			tied = false;
		}
		else if (iter->second == maxScore) {
			tied = true;
		}
	}

	//If the owner is the player, returns true
	if (owner.compare(this->playerName) == 0 && !tied)
		return true;
	else
		return false;
}

int Player::CountCardsBasedOnType(string cardType) {
	int cardCount = 0;
	vector<Card>::iterator cardIter;

	for (cardIter = this->hand.getCards().begin(); cardIter != this->hand.getCards().end(); cardIter++) {
		if (cardIter->getName().find(cardType) > 0){
			cardCount++;
		}
	}

	return cardCount;
}

int Player::ComputeAbilityScore() {
	int total = 0;
	vector<Card>::iterator cardAbilityIter;

	//We loop through all the cards, check the ability and calculate the points accordingly
	for (cardAbilityIter = this->hand.getCards().begin(); cardAbilityIter != this->hand.getCards().end(); cardAbilityIter++) {
		//First we check cards that grant 1 point per each card type, 1 card=1 point
		if (cardAbilityIter->getSpecialAbility().compare("1VPperAncient")) //1 point per ancient card
			total = total + CountCardsBasedOnType("Ancient");
		else if (cardAbilityIter->getSpecialAbility().compare("1VPperFlying")) //1 point per flying card
			total = total + CountCardsBasedOnType("Flying");
		else if (cardAbilityIter->getSpecialAbility().compare("1VPperCursedCard")) //1 point per cursed card
			total = total + CountCardsBasedOnType("Cursed");
		else if (cardAbilityIter->getSpecialAbility().compare("1VPperForestCard")) //1 point per forest card
			total = total + CountCardsBasedOnType("Forest");
		else if (cardAbilityIter->getSpecialAbility().compare("1VPperNightCard")) //1 point per night card
			total = total + CountCardsBasedOnType("Night");
		else if (cardAbilityIter->getSpecialAbility().compare("1VPperDireCard")) //1 point per dire card
			total = total + CountCardsBasedOnType("Dire");
		else if (cardAbilityIter->getSpecialAbility().compare("1VPperArcaneCard")) //1 point per dire card
			total = total + CountCardsBasedOnType("Arcane");
		//Now we handle the other cases
		else if (cardAbilityIter->getSpecialAbility().compare("1VPper3Coins")) //1 point per every 3 coins
			total = (coin / 3); //Perform integer division here
		else if (cardAbilityIter->getSpecialAbility().compare("3NobleCards=4VP")) { //4 points per every 3 noble cards
			int numOfNobleCards = CountCardsBasedOnType("Noble"); //Get the number of noble cards
			total = (numOfNobleCards / 3) * 4; //Calculate the actual score based on the number of cards
		}else if (cardAbilityIter->getSpecialAbility().compare("3VPfor2MountainCards")) { //4 points per every 3 noble cards
			int numOfMountainCards = CountCardsBasedOnType("Mountain"); //Get the number of noble cards
			total = (numOfMountainCards / 2) * 3; //Calculate the actual score based on the number of cards
		}
	}

	return total;
}
