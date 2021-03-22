#pragma once
#include "../pch.h"
#include "Player.h"
#include "../Cards/Cards.h"

Player::Player(std::string name, BiddingFacility& biddingFacility) : playerName(name), coin(0), availableArmies(0), availableCities(0), biddingFacility(biddingFacility) {}

Player::~Player() {}

//Missing assignment operator for bidding facility
Player::Player(const Player& player) : biddingFacility(player.biddingFacility) {
	this->playerName = player.playerName;
	this->coin = player.coin;
	this->availableArmies = player.availableArmies;
	this->availableCities = player.availableCities;
	this->deployedVertices = player.deployedVertices; //for vectors this is a copy
	this->hand = player.hand; //calling the assignment operator
	//this->biddingFacility(biddingFacility); //calling the assignment operator
}

Player& Player::operator =(const Player& p) {
	this->playerName = p.playerName;
	this->coin = p.coin;
	this->availableArmies = p.availableArmies;
	this->availableCities = p.availableCities;
	this->deployedVertices = p.deployedVertices; //for vectors this is a copy
	this->hand = p.hand; //calling the assignment operator
	//this->biddingFacility = p.biddingFacility; //Missing assignment operator for bidding facility
	return *this;
}

std::ostream& operator <<(std::ostream& os, const Player* p) {
	os << "Name: " << p->getPlayerName() << "\nAvailable coins: " << p->getCoins() << "\nAvailable armies: " << p->getAvailableArmies() << "\nAvailable cities: " << p->getAvailableCities();
	return os;
}


int Player::getCoins() const {
	return coin;
}

int Player::getAvailableArmies() const {
	return availableArmies;
}

int Player::getAvailableCities() const {
	return availableCities;
}

vector<Card> Player::getCards() {
	return hand.getCards();
}

std::string Player::getPlayerName() const {
	return playerName;
}

void Player::PayCoin(int coins) {
	std::cout << "Entered payCoin method" << std::endl;
}

void Player::PlaceNewArmies(Map* map, Vertex* v, int numOfArmies) {
	//The number of Armies must be more than 0
	if (numOfArmies <= 0) {
		throw PlayerActionException("Number of armies must be larger than 0");
		return;
	}

	//Player must have enough available armies
	if (availableArmies < numOfArmies) {
		std::string errorMessage = "Not enough armies to deploy, require " + std::to_string(numOfArmies) + " but only have " + std::to_string(availableArmies);
		throw PlayerActionException(errorMessage);
	}

	Territory* t = v->getTerritory();
	//You can only place new armies in the starting region or a region you owned with at least 1 city
	if (v != map->getStartingRegion() && !(t->getCitiesByPlayer(playerName) > 0)) { 
		std::string errorMessage = "Armies must be built on a starting region, or a region owned by a player with at least 1 city built";
		throw PlayerActionException(errorMessage);
	}

	//Update the number of armies and owner
	int newNumOfArmies = t->getArmiesByPlayer(playerName) + numOfArmies;
	t->setArmiesByPlayer(numOfArmies, playerName);
	availableArmies -= numOfArmies;

	//Update the list of deployed region
	if (!HasArmyDeployedInVertex(v))
		AddDeployedVertex(v);
}

void Player::MoveArmies(Map* map, Vertex* from, Vertex* to, int numOfArmies, int& remainingMoves) {
	//We perform some validation before actually moving the armies
	if (from == to) {
		throw PlayerActionException("The from and to destination is the same territory.");
	}

	int fromNumOfArmies = from->getTerritory()->getArmiesByPlayer(playerName);
	if (numOfArmies > fromNumOfArmies) {
		std::string errorMessage = "The amount of armies moved exceed the number of available armies. Need to move " + std::to_string(numOfArmies) + " but only have " + std::to_string(fromNumOfArmies);
		throw PlayerActionException(errorMessage);
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
				movementCost = numOfArmies;
			}
			else {
				movementCost = numOfArmies*3;
			}
			
			//If we dont have enough remaining moves
			if (movementCost > remainingMoves) {
				std::string errorMessage = "Not enough remaining moves to move the armies, required " + std::to_string(movementCost) + " but only have " + std::to_string(remainingMoves);
				throw PlayerActionException(errorMessage);
			}

			//Decrease the cost and move the armies
			remainingMoves -= movementCost;
			from->getTerritory()->destroyArmiesByPlayer(numOfArmies, playerName);
			to->getTerritory()->addArmiesByPlayer(numOfArmies, playerName);

			//Update the list of deployed region
			//Remove all armies from the from region if there is no remaining armies left
			int currentNumOfArmies = from->getTerritory()->getArmiesByPlayer(playerName);
			if (currentNumOfArmies == 0) {
				RemoveDeployedVertex(from);
			}
			//Add the to region to deployed regions list if it is not in it
			if (!HasArmyDeployedInVertex(to))
				AddDeployedVertex(to);

			
		}
	}
}

void Player::DestroyArmy(Vertex* v, int numOfArmies) {
	int currentNumOfArmies = v->getTerritory()->getArmiesByPlayer(playerName);
	if (currentNumOfArmies < numOfArmies) {
		std::string errorMessage = "The amount of armies to be removed exceed the number of deployed armies. Need to move " + std::to_string(numOfArmies) + " but only have " + std::to_string(currentNumOfArmies);
		throw PlayerActionException(errorMessage);
	}

	v->getTerritory()->destroyArmiesByPlayer(numOfArmies, playerName);
	availableArmies += numOfArmies;

	currentNumOfArmies = v->getTerritory()->getArmiesByPlayer(playerName);
	if (currentNumOfArmies == 0) {
		RemoveDeployedVertex(v);
	}
}

void Player::BuildCity(Vertex* v, int numOfCities) {
	if (availableCities < numOfCities) {
		std::string errorMessage = "The amount of cities to be built is not sufficient. Need to build " + std::to_string(numOfCities) + " but only have " + std::to_string(availableCities);
		throw PlayerActionException(errorMessage);
	}

	if (v->getTerritory()->getArmiesByPlayer(playerName) == 0) {
		throw PlayerActionException("City must be built in a region with at least 1 army of the player");
	}

	v->getTerritory()->addCitiesByPlayer(numOfCities, playerName);
	availableCities -= numOfCities;
}

void Player::InitResources(int coin, int armies, int cities) {
	this->coin = coin;
	this->availableArmies = armies;
	this->availableCities = cities;
}

bool Player::HasArmyDeployedInVertex(Vertex* v) {
	for (vector<Vertex*>::iterator vertexIter = deployedVertices.begin(); vertexIter != deployedVertices.end(); vertexIter++) {
		if (*vertexIter == v)
			return true;
	}

	return false;
}

void Player::AddDeployedVertex(Vertex* v) {
	deployedVertices.push_back(v);
}

void Player::RemoveDeployedVertex(Vertex* v) {
	deployedVertices.erase(std::remove(deployedVertices.begin(), deployedVertices.end(), v), deployedVertices.end());
}

int Player::ComputeScore(Map* map) {
	cout << "Starting score calculation of player " << this->playerName << ": " << endl;

	//Calculating the territories owned by the player
	/*int ownedTerritoriesScore = this->territories.size();
	cout << "Territories score: " << ownedTerritoriesScore << endl;

	int ownedContinentsScore = ComputeRegionalScore(map);
	cout << "Continents score: " << ownedContinentsScore << endl;

	int abilityScore = ComputeAbilityScore();
	cout << "Ability score: " << abilityScore << endl;

	int total = ownedTerritoriesScore + ownedContinentsScore + abilityScore;
	cout << "Total score: " << total << endl;*/

	return ComputeTerritoryScore() + ComputeRegionalScore(map);
}

int Player::ComputeTerritoryScore() {
	//The territory score equals to the number of regions owned
	return deployedVertices.size();
}

int Player::ComputeRegionalScore(Map* map) {
	int continentPoints = 0;

	//Calculating the regional score of all players
	//Initializing the point accumlator to store the points of all players
	std::map<string, std::map<string, int>> pointAccumulator;
	for (vector<Continent*>::iterator continentIter = map->continents().begin(); continentIter != map->continents().end(); continentIter++) {
		std::map<string, int> playerPointsPerRegion;
		pointAccumulator.insert(pair<string, std::map<string, int>>((**continentIter).name, playerPointsPerRegion));
	}

	//For each vertex (territory) owned by each player, we add 1 point to that player
	for (vector<Vertex*>::iterator vertexIter = map->vertices().begin(); vertexIter != map->vertices().end(); vertexIter++) {
		Territory* t = (**vertexIter).getTerritory();
		string owner = t->getOwner();
		std::map<string, int> continentPoints = pointAccumulator[t->getContinent()];

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
	/*string owner = "";
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
		return false;*/
	std::map<std::string, int>::iterator owner = std::max_element(continentScores.begin(), continentScores.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b)->bool { return a.second < b.second; });
	return owner->first == playerName;
}

int Player::CountCardsBasedOnType(string cardType) {
	int cardCount = 0;
	vector<Card>::iterator cardIter;

	for (cardIter = hand.getCards().begin(); cardIter != hand.getCards().end(); cardIter++) {
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

PlayerActionException::PlayerActionException(const std::string& msg) : errorMessage(msg) {}

const char* PlayerActionException::what() const throw ()
{
	return errorMessage.c_str();
}
