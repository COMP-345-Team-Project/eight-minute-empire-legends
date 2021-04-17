#pragma once
#include "../pch.h"
#include "Player.h"
#include "../Cards/Cards.h"
//#include "PlayerStrategies.h"

Player::Player(std::string name, BiddingFacility* biddingFacility, bool isNeutral) : isNeutral(isNeutral), playerName(name), coin(0), availableArmies(0), availableCities(0), biddingFacility(biddingFacility), elixir(0), playerScore() {}
Player::Player(std::string name, BiddingFacility* biddingFacility) : isNeutral(false), playerName(name), coin(0), availableArmies(0), availableCities(0), biddingFacility(biddingFacility), elixir(0), playerScore() {}

Player::~Player() {
	vector<Card*>::iterator cardItter;
	for (cardItter = this->cards.begin(); cardItter != cards.end(); cardItter++)
	{
		delete *cardItter;
	}
}

//Missing assignment operator for bidding facility
Player::Player(const Player& player){
	this->playerName = player.playerName;
	this->coin = player.coin;
	this->availableArmies = player.availableArmies;
	this->availableCities = player.availableCities;
	this->deployedVertices = player.deployedVertices; //for vectors this is a copy
	this->cards = player.cards; //calling the assignment operator
	this->biddingFacility = player.biddingFacility; //calling the assignment operator
	this->elixir = player.elixir;
	this->playerScore = player.playerScore;
}

Player& Player::operator =(const Player& p) {
	this->playerName = p.playerName;
	this->coin = p.coin;
	this->availableArmies = p.availableArmies;
	this->availableCities = p.availableCities;
	this->deployedVertices = p.deployedVertices; //for vectors this is a copy
	this->cards = p.cards; //calling the assignment operator
	this->biddingFacility = p.biddingFacility; //calling the assignment operator
	this->elixir = p.elixir;
	this->playerScore = p.playerScore;
	return *this;
}

std::ostream& operator <<(std::ostream& os, const Player* p) {
	os << "Name: " << p->getPlayerName() << "\nAvailable coins: " << p->getCoins() << "\nAvailable armies: " << p->getAvailableArmies() << "\nAvailable cities: " << p->getAvailableCities();
	return os;
}

bool Player::isNeutralPlayer() {
	return isNeutral;
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

vector<Card*> Player::getCards() {
	return cards;
}

void Player::addCard(Card* card) {
	cards.push_back(card);	
}

std::string Player::getPlayerName() const {
	return playerName;
}

vector<Vertex*> Player::GetDeployedVertices() {
	return deployedVertices;
}

void Player::BuyCard(Card* cardBought, int costs) {
	// These boys are nuked in the player destructor
	cards.push_back(new Card(*cardBought));
	PayCoin(costs);	
}

void Player::PayCoin(int amount) {
	if (amount > coin)
		throw PlayerActionException("Insufficient fund");

	coin -= amount;

	lastActionMessage = "Paid " + amount + std::to_string(amount) + " coin(s).";	
	notify();
}

void Player::addElixirs(int elixir) {
	this->elixir += elixir;
}

int Player::getElixirs() {
	return this->elixir;
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
	if (v != map->getStartingRegion() && !(t->getCitiesByPlayer(playerName) > 0) && !isNeutral) { 
		std::string errorMessage = "Armies must be built on a starting region, or a region owned by a player with at least 1 city built";
		throw PlayerActionException(errorMessage);
	}

	//Update the number of armies and owner
	int newNumOfArmies = t->getArmiesByPlayer(playerName) + numOfArmies;
	t->setArmiesByPlayer(newNumOfArmies, playerName);
	availableArmies -= numOfArmies;

	//Update the list of deployed region
	if (!HasArmyDeployedInVertex(v))
		AddDeployedVertex(v);

	lastActionMessage = "Deployed " + std::to_string(numOfArmies) + " armie(s) to " + v->getTerritory()->getName();
	notify();
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

	lastActionMessage = "Moved " + std::to_string(numOfArmies) + " armie(s) from " + from->getTerritory()->getName() + " to " + to->getTerritory()->getName() + 
		". " + std::to_string(remainingMoves) + " move(s) remain.";
	notify();
}

void Player::DestroyArmy(Vertex* v, Player* opponent, int numOfArmies) {
	int playerArmies = v->getTerritory()->getArmiesByPlayer(playerName);
	if (playerArmies <= 0) {
		std::string errorMessage = "You must have at least 1 army in this region to destroy the opponent armies";
		throw PlayerActionException(errorMessage);
	}

	int opponentArmies = v->getTerritory()->getArmiesByPlayer(opponent->getPlayerName());
	if (opponentArmies < numOfArmies) {
		std::string errorMessage = "The amount of armies to be removed exceed the number of deployed armies. Need to destroy " + std::to_string(numOfArmies) + " but only have " + std::to_string(opponentArmies);
		throw PlayerActionException(errorMessage);
	}

	v->getTerritory()->destroyArmiesByPlayer(numOfArmies, opponent->getPlayerName());
	opponent->availableArmies += numOfArmies;

	opponentArmies = v->getTerritory()->getArmiesByPlayer(opponent->getPlayerName());
	if (opponentArmies == 0) {
		opponent->RemoveDeployedVertex(v);
	}

	lastActionMessage = "Defeated " + std::to_string(numOfArmies) + " of " + opponent->getPlayerName() + "'s armies";
	notify();
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

	lastActionMessage = "Built " + std::to_string(numOfCities) + " citie(s) in " + v->getTerritory()->getName();
	notify();
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

int Player::ComputeScore(Map* map, vector<Player*> players) {
	playerScore.clearScores();
	ComputeTerritoryScore();
	ComputeRegionalScore(map);
	ComputeAbilityScore();
	ComputeElixirScore(players);

	return playerScore.getTotalScore();
}

int Player::ComputeTerritoryScore() {
	//The territory score equals to the number of regions owned
	for (vector<Vertex*>::iterator vertexIter = deployedVertices.begin(); vertexIter != deployedVertices.end(); vertexIter++) {
		if ((**vertexIter).getTerritory()->getOwner().compare(playerName) == 0) {
			playerScore.addOwnedTerritories((**vertexIter).getTerritory()->getName());
		}
	}

	return playerScore.getTerritoryScore();
}

int Player::ComputeRegionalScore(Map* map) {
	int continentPoints = 0;
	//Calculating the regional score of all players
	//Initializing the point accumlator to store the points of all players
	std::map<string, std::map<string, int>> pointAccumulator; 
	
	for (int i = 0; i < map->continents().size(); i++) {
		std::map<string, int> playerPointsPerRegion;
		pointAccumulator.insert(pair<string, std::map<string, int>>(map->continents().at(i)->name, playerPointsPerRegion));
	}

	for (int i = 0; i < map->vertices().size(); i++) {
		Territory* t = map->vertices().at(i)->getTerritory();
		string owner = t->getOwner();

		//If someone actually owns the continent
		if (owner.compare("") != 0) {
			std::map<string, int> continentPoints = pointAccumulator[t->getContinent()];

			if (continentPoints.find(owner) == continentPoints.end()) {
				continentPoints.insert(pair<string, int>(owner, 0));
			}

			continentPoints[owner]++;
			pointAccumulator[t->getContinent()] = continentPoints;
		}
	}

	//Now we check if this player has the maximum points in each continent
	for (std::map<string, std::map<string, int>>::iterator iter = pointAccumulator.begin(); iter != pointAccumulator.end(); ++iter) {
		if (this->OwnsContinent(iter->second)) {
			playerScore.addOwnedContinents(iter->first);
		}
	}

	return playerScore.getContinentScore();
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
	std::string ownerName = owner->first;
	int ownerArmies = owner->second;

	//We must check that there is only 1 player that owns the continent
	for (std::map<std::string, int>::iterator mapIter = continentScores.begin(); mapIter != continentScores.end(); mapIter++) {
		if (mapIter->first.compare(ownerName) != 0 && mapIter->second == ownerArmies) {
			ownerName = "";
			break;
		}
	}
	
	return ownerName == playerName;
}

int Player::ComputeElixirScore(vector<Player*> players) {
	vector<Player*>::iterator player = std::max_element(players.begin(), players.end(), [](Player* a, Player* b)->bool { return a->getElixirs() < b->getElixirs(); });
	int maxElixirs = (**player).getElixirs();
	std::string playerNameWithMaxElixir = (**player).getPlayerName();

	//If the player with the maximum of elixir is not the player
	if (playerNameWithMaxElixir.compare(playerName) != 0){
		return 0;
	}
		

	//Else we check if there is a tied between players
	for (vector<Player*>::iterator iter = players.begin(); iter != players.end(); ++iter) {
		if ((**iter).getElixirs() == maxElixirs && playerNameWithMaxElixir.compare(playerName) != 0) {
			//If the player ties with another player for the amount of elixirs
			playerScore.setElixirScore(1);
			return playerScore.getElixirScore();
		}
	}

	//Player has the most amount of elixir
	playerScore.setElixirScore(2);
	return playerScore.getElixirScore();
}

int Player::CountCardsBasedOnType(string cardType) {
	int cardCount = 0;
	vector<Card*>::iterator cardIter;

	for (cardIter = cards.begin(); cardIter != cards.end(); cardIter++) {
		if ((**cardIter).getName().find(cardType) != string::npos){
			cardCount++;
		}
	}

	return cardCount;
}

int Player::ComputeAbilityScore() {
	int total = 0;
	vector<Card>::iterator cardAbilityIter;

	for (int i = 0; i < cards.size(); i++) {
		std::string specialAbility = cards.at(i)->getSpecialAbility();
		playerScore.addAbility(specialAbility);
		//First we check cards that grant 1 point per each card type, 1 card=1 point
		if (specialAbility.compare("1VPperAncient") == 0) //1 point per ancient card
			total += CountCardsBasedOnType("Ancient");
		else if (specialAbility.compare("1VPperFlying") == 0) //1 point per flying card
			total += CountCardsBasedOnType("Flying");
		else if (specialAbility.compare("1VPperCursedCard") == 0) //1 point per cursed card
			total += CountCardsBasedOnType("Cursed");
		else if (specialAbility.compare("1VPperForestCard") == 0) //1 point per forest card
			total += CountCardsBasedOnType("Forest");
		else if (specialAbility.compare("1VPperNightCard") == 0) //1 point per night card
			total += CountCardsBasedOnType("Night");
		else if (specialAbility.compare("1VPperDireCard") == 0) //1 point per dire card
			total += CountCardsBasedOnType("Dire");
		else if (specialAbility.compare("1VPperArcaneCard") == 0) //1 point per dire card
			total += CountCardsBasedOnType("Arcane");
		//Now we handle the other cases
		else if (specialAbility.compare("1VPper3Coins") == 0) //1 point per every 3 coins
			total += (coin / 3); //Perform integer division here
		else if (specialAbility.compare("3NobleCards=4VP") == 0) { //4 points per every 3 noble cards
			int numOfNobleCards = CountCardsBasedOnType("Noble"); //Get the number of noble cards
			total += (numOfNobleCards / 3) * 4; //Calculate the actual score based on the number of cards
		}
		else if (specialAbility.compare("3VPfor2MountainCards") == 0) { //4 points per every 3 noble cards
			int numOfMountainCards = CountCardsBasedOnType("Mountain"); //Get the number of noble cards
			total += (numOfMountainCards / 2) * 3; //Calculate the actual score based on the number of cards
		}
	}

	playerScore.setAbilityScore(total);
	return total;
}

int Player::GetTerritoriesScore() {
	return playerScore.getTerritoryScore();
}

int Player::GetContinentsScore() {
	return playerScore.getContinentScore();
}

int Player::GetAbilitiesScore() {
	return playerScore.getAbilityScore();
}

int Player::GetElixirScore() {
	return playerScore.getElixirScore();
}

int Player::GetTotalScore() {
	return playerScore.getTotalScore();
}

PlayerScore Player::getPlayerScore() {
	return playerScore;
}

PlayerActionException::PlayerActionException(const std::string& msg) : errorMessage(msg) {}

const char* PlayerActionException::what() const throw ()
{
	return errorMessage.c_str();
}

//Strategy
void Player::setStrategy(string strategyName) {
	delete strategy;

	if (strategyName == "GreedyComputer")
		strategy = new GreedyStrategy();
	else if (strategyName == "ModerateComputer")
		strategy = new ModerateStrategy();
	else {
		strategy = new HumanStrategy();
	}

}

void Player::notify() {
	std::list<Observer*>::iterator i = _observers->begin();
	for (; i != _observers->end(); ++i)
		(*i)->update();
}

Strategy* Player::getStrategy() {
	return strategy;
}

std::string Player::getLastActionMessage() {
	return lastActionMessage;
}

void PlayerBuilder::setPlayersType(vector<Player*> players) {
	for (Player* pl : players) {
		string playerType;
		std::cout << "Type of player for " << pl->getPlayerName() << " (H)uman, (G)reedy Computer or (M)oderate Computer :" << endl;
		std::cin >> playerType;

		if (playerType == "G" || playerType == "g") {
			pl->setStrategy("GreedyComputer");
			std::cout << pl->getPlayerName() << " is a Greedy Computer" << endl;
		}

		else if (playerType == "M" || playerType == "m") {
			pl->setStrategy("ModerateComputer");
			std::cout << pl->getPlayerName() << " is a Moderate Computer" << endl;
		}

		else {
			pl->setStrategy("Human");
			std::cout << pl->getPlayerName() << " is a Human" << endl;
		}
	}
}
