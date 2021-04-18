#pragma once

#include "../pch.h"
#include "GameCore.h"
#include "../Utilities/Utilities.h"

// Resources class implementation

Resources::Resources() {
	this->coins = _dCoins;
	this->armies = _dArmies;
	this->cities = _dCities;
}

Resources::Resources(int coins, int armies, int cities) {
	this->coins = coins;
	this->armies = armies;
	this->cities = cities;
}

void Resources::assignInitialResources(vector<Player*> players) {
	for (Player* pl : players) {
		pl->InitResources(this->coins, this->armies, this->cities);
	}
}

int Resources::getAssignedCities() {
	return this->cities;
}

std::ostream& operator <<(std::ostream& os, const Resources* r) {
	os << "coins : " << r->coins << std::endl << "armies : " << r->armies << std::endl << "cities : " << r->cities;
	return os;
}

// Game class implementation.

Game::Game(Resources* resources, Map* map, Deck* deck, vector<Player*> players) : Observable(){
	this->resources = resources;
	this->map = map;
	this->deck = deck;
	this->players = players;
	if (players.size() == 2) {
		this->neutralPlayer = new Player("NeutralPlayer", nullptr, true);
		neutralPlayer->InitResources(0, 10, 0);
	}
}

Game::Game() : Observable() { //For testing only
	this->resources = NULL;
	this->map = NULL;
	this->deck = NULL;
	this->endGameCardCount = 0;
} 

// TODO: We sure about this? Pretty sure whoever builds it should destroy it, 
// so Game shouldn't be destroying it's injected dependencies.
Game::~Game() {
	delete this->map;
	for (Player* pl : this->players) {
		delete pl;
	}
	if (neutralPlayer != nullptr) {
		delete neutralPlayer;
	}
}

Resources* Game::getResources() {
	return this->resources;
}

Map* Game::getMap() {
	return this->map;
}

Deck* Game::getDeck() {
	return this->deck;
}

std::vector<Player*> Game::getPlayers() {
	return this->players;
}

void Game::endGame() {
	endGame(map, players);
}

void Game::endGame(Map* map, vector<Player*> players) {
	//Please dont remove this code because this is optimize for a variable number of players
	/*std::map<std::string, int> scores;
	
	for (vector<Player*>::iterator playerIter = players.begin(); playerIter != players.end(); playerIter++) {
		scores.insert(pair<std::string, int>((**playerIter).getPlayerName(), (**playerIter).ComputeScore(map, players)));
	}

	//We find the player with the maximum score
	std::map<std::string, int>::iterator winner = std::max_element(scores.begin(), scores.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b)->bool { return a.second < b.second; });
	std::string winnerName = winner->first;
	int winnerScore = winner->second;

	//We check to make sure that there is no tie
	bool isTied = false;
	for (vector<Player*>::iterator playerIter = players.begin(); playerIter != players.end(); playerIter++) {
		std::string currPlayerName = (**playerIter).getPlayerName();
		if (currPlayerName.compare(winnerName) != 0 && scores[currPlayerName] == winnerScore) {
			isTied = true;
			break;
		}
	}
	//No tied based on score
	if (!isTied) {
		std::cout << "The winner is player: " << winnerName << std::endl;
		return;
	}

	//We next check the number of coins
	std::vector<Player*>::iterator mostCoinPlayer = std::max_element(players.begin(), players.end(), [](const Player* a, const Player* b)->bool { return a->getCoins() < b->getCoins(); });
	winnerName = (**mostCoinPlayer).getPlayerName();
	int winnerCoins = (**mostCoinPlayer).getCoins();
	isTied = false;
	for (vector<Player*>::iterator playerIter = players.begin(); playerIter != players.end(); playerIter++) {
		if ((**playerIter).getPlayerName().compare(winnerName) != 0 && (**playerIter).getCoins() == winnerCoins) {
			isTied = true;
			break;
		}
	}
	//No tied based on coins
	if (!isTied) {
		std::cout << "The winner is player: " << winnerName << std::endl;
		return;
	}*/

	//Assume we only have 2 players for now
	std::cout << "\n--------------Game ended, now Computing Scores-----------"<< std::endl;
	if (players.size() == 2) {
		Player* p1 = players.at(0);
		Player* p2 = players.at(1);
		
		//First we compare the scores
		int p1Score = p1->ComputeScore(map, players);
		int p2Score = p2->ComputeScore(map, players);

		std::cout << p1->getPlayerName() << "'s score is: " << p1Score << std::endl;
		std::cout << p2->getPlayerName() << "'s score is: " << p2Score << std::endl;

		if (p1Score > p2Score) {
			std::cout << "The winner is player: " << p1->getPlayerName() << std::endl;
			notify();
			return;
		}
		else if (p1Score < p2Score) {
			std::cout << "The winner is player: " << p2->getPlayerName() << std::endl;
			notify();
			return;
		}

		//If there is a tie, we compare the number of coins
		std::cout << "Both players tied, comparing remmaining coins" << std::endl;
		if (p1->getCoins() > p2->getCoins()) {
			std::cout << "The winner is player: " << p1->getPlayerName() << std::endl;
			notify();
			return;
		}
		else if (p1->getCoins() < p2->getCoins()) {
			std::cout << "The winner is player: " << p2->getPlayerName() << std::endl;
			notify();
			return;
		}

		//If there is a tie, we then compare the number of controlled regions
		std::cout << "Both players have the same amount of coins, comparing controlled regions" << std::endl;
		int p1RegionScore = p1->GetTerritoriesScore();
		int p2RegionScore = p2->GetTerritoriesScore();

		if (p1RegionScore > p2RegionScore) {
			std::cout << "The winner is player: " << p1->getPlayerName() << std::endl;
			notify();
			return;
		}
		else if (p1RegionScore < p2RegionScore) {
			std::cout << "The winner is player: " << p2->getPlayerName() << std::endl;
			notify();
			return;
		}

		std::cout << " This game is a tie!" << std::endl;
		notify();
	}
	else {
		std::cout << " Current number of players not supported!" << std::endl;
	}
}

void Game::displayTerritories(std::vector<Vertex*> vertices) {
	displayTerritories(vertices, false);
}

void Game::displayTerritories(std::vector<Vertex*> vertices, bool numbered) {
	int number = 0;
	for (Vertex* v : vertices) {
		if (numbered) {
			std::cout << "\n( " << number++ << " ) -------------------------" << std::endl;
		}
		else {
			std::cout << "\n-------------------------------" << std::endl;
		}
		std::cout << "      Territory :      " << v->getTerritory()->getName() << std::endl;
		std::cout << "      Owner :          " << v->getTerritory()->getOwner() << std::endl;
		std::cout << "      Continent :      " << v->getTerritory()->getContinent() << std::endl;
		if (neutralPlayer != nullptr) {
		std::cout << "      Neutral Armies : " << v->getTerritory()->getArmiesByPlayer(neutralPlayer->getPlayerName()) << std::endl;
		}
		std::cout << "  --- Armies ---" << std::endl;
		for (Player* pl : this->getPlayers()) {
			std::cout << "      " << pl->getPlayerName() << " - " << v->getTerritory()->getArmiesByPlayer(pl->getPlayerName()) << std::endl; 
		}	
		
		std::cout << "  --- Cities ---" << std::endl;
		for (Player* pl : this->getPlayers()) {
			std::cout << "      " << pl->getPlayerName() << " - " << v->getTerritory()->getCitiesByPlayer(pl->getPlayerName()) << std::endl;
		}
		std::cout << std::endl;
		
	}
}

std::ostream& operator <<(std::ostream& os, const Game* g) {
	os << g->resources << std::endl;
	os << g->map;
	os << std::endl;
	for (Player* pl : g->players) {
		os << pl << std::endl;
	}	
	return os;
}

// Startup Phase

void Game::runSetupPhase(int maxNumOfCards) {
	_assignResources();
	_bid();
	_placeArmies();
	_setEndGameConditions(maxNumOfCards);
}
void Game::_placeArmies() {
	std::vector<Vertex*> possibleStartingVertices = map->getPotentialStartingRegions();
	
	std::cout << "Please choose a starting region from among the following:\n" << endl;
	displayTerritories(possibleStartingVertices, true);
	std::cout << "Enter the number of your choice here: ";
	int chosenStartingVertexIndex;
	std::cin >> chosenStartingVertexIndex;
	if (chosenStartingVertexIndex < 0 || chosenStartingVertexIndex >= possibleStartingVertices.size()) {
		cout << "Invalid choice. Defaulting to the first option on the list above.";
		chosenStartingVertexIndex = 0;
	}

	map->setStartingRegion(possibleStartingVertices[chosenStartingVertexIndex]);

	// Place initial armies in starting territory
	for (Player* player :  players) {
		int numStartingArmies = 4;
		player->PlaceNewArmies(
			this->map, this->map->getStartingRegion(), numStartingArmies);
	}

	//Special Case for 2 players game
	if (players.size() == 2) {
		// Take turns placing a neutral army.
		std::cout << "\nSetting up neutral armies...\n" << endl;
		while (neutralPlayer->getAvailableArmies()) {
			assert(neutralPlayer->getAvailableArmies() >= players.size());
			for (Player* player : players) {
				std::cout << "\n\n" << player->getPlayerName() << ",  choose a territory in which to place a neutral army:" << endl;
				displayTerritories(map->vertices(), true);
				int choice;
				std::cout << "Enter the number of your choice here: ";
				std::cin >> choice;
				if (choice < 0 || choice >= map->vertices().size()) {
					cout << "Invalid choice. Defaulting to the first option on the list above.";
					choice = 0;
				}
				neutralPlayer->PlaceNewArmies(map, map->vertices()[choice], 1);
				std::cout << "There are  " << neutralPlayer->getAvailableArmies() << "  neutral armies left to add to the board.";
			}
		}
	}
}
void Game::_assignResources() {

	std::cout << "Resources Initialization..." << endl;
	for (int i = 0; i < players.size(); i++) {

		if (players.size() == 2) {
			players[i]->InitResources(14, 18, 3);
		}

		if (players.size() == 3) {
			players[i]->InitResources(11, 18, 3);
		}

		if (players.size() == 4) {
			players[i]->InitResources(9, 18, 3);
		}

		std::cout << "Player " << players[i]->getPlayerName() << " has " << players[i]->getCoins() << " coins" << endl;
	}
}
void Game::_bid() {

	int numPlayers = players.size();

	string tempInput;
	int playerBid;

	BidTieBreakerByLastName tieBreaker;
	BiddingFacility biddingFacility = BiddingFacility(tieBreaker);

	//Player Bidding

	std::cout << "Bidding..." << endl;
	for (int i = 0; i < numPlayers; i++) {

		std::cout << "Player " << players[i]->getPlayerName() << ", How much do you want to bid to start the game: ";
		std::cin >> tempInput;


		try {
			playerBid = std::stoi(tempInput);
		}
		catch (...) {
			playerBid = 0;
		}

		if (playerBid > players[i]->getCoins() || playerBid < 0) {
			std::cout << "!Invalid bid! Your bid is default to 0" << endl;
		}
		else {
			std::cout << "Your bid is: " << playerBid << endl;
		}

		BidSubmission playerBidSubmission = BidSubmission(to_string(i), players[i]->getPlayerName(), playerBid);
		biddingFacility.trySubmitBid(playerBidSubmission);
	}

	//Resolving bid

	int bidWinner = std::stoi(biddingFacility.getWinningBid().getPlayerID());
	int bidAmount = biddingFacility.getWinningBid().getBidAmount();

	std::cout << "The bidding winner is Player " << bidWinner + 1 << ": " << players[bidWinner]->getPlayerName() << " at " << bidAmount << " coins" << endl;

	//Changing playing order of the game
	Player* playerTemp = players[bidWinner];

	players.insert(players.begin(), playerTemp);
	players.erase(players.begin() + bidWinner + 1);

	//Winner of the bidding pays coins
	players[0]->PayCoin(bidAmount);

	//New order of game play determined
	std::cout << "The new order of game play is as following: " << endl;
	for (int i = 0; i < players.size(); i++) {

		std::cout << "Player " << i + 1 << ": " << players[i]->getPlayerName() << endl;
	}

}

void Game::_setEndGameConditions(int maxNumOfCards) {
	if (maxNumOfCards == 0) {
		//Game ends when each players have certain numbers of cards
		endGameCardCount = 13;
		if (players.size() == 3) {
			endGameCardCount = 10;
		}
		if (players.size() == 4) {
			endGameCardCount = 8;
		}
	}
	else {
		endGameCardCount = maxNumOfCards;
	}
}

void Game::runRoundsUntilEndGame() {
	//Creating a CardSpace
	CardSpace cardSpace = CardSpace(*deck);
	PlayerBuilder::setPlayersType(players);

	PlayerBuilder::setPlayersType(players);

	int gameRound = 1;

	//Main loop until game ends
	while (players[players.size() - 1]->getCards().size() < endGameCardCount) {

		std::cout << "\n\nRound " << gameRound++ << endl;

		string changeStrategy = "N";
		std::cout << "Do you wish to change the strategy of any players? (Y)es or (N)o:";
		std::cin >> changeStrategy;

		if (changeStrategy == "Y" || changeStrategy == "y") {
			PlayerBuilder::setPlayersType(players);
		}

		for (int i = 0; i < players.size(); i++) {

			//Buy card based on strategy of each player
			Card* cardBeingPurchased = players[i]->getStrategy()->buyCard(players[i], cardSpace, *deck);

			//Perform action based on strategy of each player
			players[i]->getStrategy()->performAction(this,players[i],cardBeingPurchased);
			
			
		}

	}
}

void Game::_performAction(Card* card, Player* player, int actionOrder) {
	//Perform the first action
	std::cout << "Perform action ";

	std::string action = "";
	if (actionOrder == 1) {
		card->printHelper(card->getFirstAction());
		action = card->getFirstAction();
	}
	else {
		card->printHelper(card->getSecondAction());
		action = card->getSecondAction();
	}

	std::cout << "? (Y/N)";

	if (confirm()) {
		if (action.compare("newArmy") == 0) {
			PlaceArmies(player, card->getNewArmy());
		}
		else if (action.compare("moveArmy") == 0) {
			MoveArmies(player, card->getMoveArmy());
		}
		else if (action.compare("buildCity") == 0) {
			BuildCity(player);
		}
		else if (action.compare("destroyArmy") == 0) {
			DestroyArmies(player, card->getDestroyArmy());
		}
		else {
			std::cout << "Unknown action.";
		}
	}

	//We update the statistics everytime an action is done
	notify();
}

void Game::PlaceArmies(Player* player, int deployLimit) {
	bool placeMoreArmies = true;
	while (deployLimit > 0 && placeMoreArmies) {

		//Get the vertices where you can deploy your armies
		vector<Vertex*> deployableVertices;

		for (int i = 0; i < map->vertices().size(); i++) {
			Vertex* currVertex = map->vertices().at(i);
			if (currVertex == map->getStartingRegion() || currVertex->getTerritory()->getCitiesByPlayer(player->getPlayerName())) {
				deployableVertices.push_back(currVertex);
			}
		}

		if (deployableVertices.size() == 0) {
			std::cout << "No deployable regions! " << deployLimit << std::endl;
			return;
		}

		//Display the vertex where armies can be added
		std::cout << "\nRemaining armies to deployed: " << deployLimit << std::endl;

		//Let the user select a vertex
		Vertex* chosenVertex = deployableVertices.at(_getVertexIndexFromUserInput(deployableVertices, "Select the territory you would like to deploy: "));

		//Let the user select how many armies to deploy
		int tobeDeployed = _getArmiesForOperation(deployLimit);

		//Deploying the armies
		try {
			player->PlaceNewArmies(map, chosenVertex, tobeDeployed);
			deployLimit -= tobeDeployed;
			std::cout << "Armies deployed successfully." << std::endl;
		}
		catch (PlayerActionException& ex) {
			std::cout << ex.what() << std::endl;
		}
		
		//Ask the player if he wants to continue
		if (deployLimit > 0) {
			std::cout << "Do you want to continue deploying? (Y/N) ";
			if (!confirm()) {
				placeMoreArmies = false;
			}
		}
		else {
			std::cout << "No more armies to deploy. ";
		}
	}
	std::cout << "Finish placing new armies." << std::endl;
}

void Game::autoPlaceArmies(Player* player, int deployLimit) {

	//Get the vertices where you can deploy your armies
	vector<Vertex*> deployableVertices;

	for (int i = 0; i < map->vertices().size(); i++) {
		Vertex* currVertex = map->vertices().at(i);
		if (currVertex == map->getStartingRegion() || currVertex->getTerritory()->getCitiesByPlayer(player->getPlayerName())) {
			deployableVertices.push_back(currVertex);
		}
	}

	if (deployableVertices.size() == 0) {
		std::cout << "No deployable regions! " << deployLimit << std::endl;
		return;
	}

	//Display the vertex where armies can be added
	std::cout << "\nRemaining armies to deployed: " << deployLimit << std::endl;

	//Select the first vertex available
	Vertex* chosenVertex = deployableVertices.at(0);

	//Place all armies from this card to the above chosen vertex
	int tobeDeployed = deployLimit;

	//Deploying the armies
	try {
		player->PlaceNewArmies(map, chosenVertex, tobeDeployed);
		deployLimit -= tobeDeployed;
		std::cout << "Armies deployed successfully." << std::endl;
	}
	catch (PlayerActionException& ex) {
		std::cout << ex.what() << std::endl;
	}
	
	std::cout << "Finish placing new armies." << std::endl;
}

void Game::MoveArmies(Player* player, int moveLimit) {
	bool moveMoreArmies = true;
	while (moveLimit > 0 && moveMoreArmies) {
		//Display the vertex where armies can be added
		std::cout << "\nRemaining moves: " << moveLimit << std::endl;

		//Get the vertices where you have armies deployed
		vector<Vertex*> fromVertices;
		for (int i = 0; i < map->vertices().size(); i++) {
			Vertex* currVertex = map->vertices().at(i);
			if (currVertex->getTerritory()->getArmiesByPlayer(player->getPlayerName()) > 0) {
				fromVertices.push_back(currVertex);
			}
		}

		if (fromVertices.size() == 0) {
			std::cout << "You do not have any regions with armies! " << std::endl;
			return;
		}

		Vertex* fromVertex = fromVertices.at(_getVertexIndexFromUserInput(fromVertices, "Select the region where your armies is located: "));

		//Get the vertices where you can move your armie to
		vector<Vertex*> toVertices = map->adjacentVertices(fromVertex);
		Vertex* toVertex = toVertices.at(_getVertexIndexFromUserInput(toVertices, "Select the destination region: "));

		//Let the user select how many armies to move
		int armiesMoved = _getArmiesForOperation(moveLimit);

		//Deploying the armies
		try {
			player->MoveArmies(map, fromVertex, toVertex, armiesMoved, moveLimit);
			std::cout << "Armies moved successfully." << std::endl;
		}
		catch (PlayerActionException& ex) {
			std::cout << ex.what() << std::endl;
		}

		//Ask the player if he wants to continue
		if (moveLimit > 0) {
			std::cout << "Do you want to continue moving? (Y/N) ";
			if (!confirm()) {
				moveMoreArmies = false;
			}
		}
		else {
			std::cout << "No more moves. ";
		}
	}
	std::cout << "Finished moving armies." << std::endl;
}

void Game::autoMoveArmies(Player* player, int moveLimit) {

	//Display the vertex where armies can be added
	std::cout << "\nRemaining moves: " << moveLimit << std::endl;

	//Get the vertices where you have armies deployed
	vector<Vertex*> fromVertices;
	for (int i = 0; i < map->vertices().size(); i++) {
		Vertex* currVertex = map->vertices().at(i);
		if (currVertex->getTerritory()->getArmiesByPlayer(player->getPlayerName()) > 0) {
			fromVertices.push_back(currVertex);
		}
	}

	if (fromVertices.size() == 0) {
		std::cout << "You do not have any regions with armies! " << std::endl;
		return;
	}

	//Move from first available vertex
	Vertex* fromVertex = fromVertices.at(0);

	//Move to first available vertex
	vector<Vertex*> toVertices = map->adjacentVertices(fromVertex);
	Vertex* toVertex = toVertices.at(0);

	//Move all armies available from the card
	int armiesMoved = moveLimit;

	//Deploying the armies
	try {
		player->MoveArmies(map, fromVertex, toVertex, armiesMoved, moveLimit);
		std::cout << "Armies moved successfully." << std::endl;
	}
	catch (PlayerActionException& ex) {
		std::cout << ex.what() << std::endl;
	}

	
	std::cout << "Finished moving armies." << std::endl;
}

void Game::BuildCity(Player* player) {
	bool continueBuilding = true;

	while (continueBuilding) {
		//Get the vertices where you have armies deployed
		vector<Vertex*> validVertices;
		for (int i = 0; i < map->vertices().size(); i++) {
			Vertex* currVertex = map->vertices().at(i);
			if (currVertex->getTerritory()->getArmiesByPlayer(player->getPlayerName()) > 0) {
				validVertices.push_back(currVertex);
			}
		}

		if (validVertices.size() == 0) {
			std::cout << "You do not have any regions with armies! " << std::endl;
			return;
		}

		Vertex* buildVertex = validVertices.at(_getVertexIndexFromUserInput(validVertices, "Select a region where your armies is located: "));

		//Deploying the armies
		try {
			//We build 1 city at a time only
			player->BuildCity(buildVertex, 1);
			continueBuilding = false;
		}
		catch (PlayerActionException& ex) {
			std::cout << ex.what() << std::endl;
		}

		//Ask the player if he wants to continue
		if (continueBuilding) {
			std::cout << "Do you want to continue building? (Y/N) ";
			if (!confirm()) {
				continueBuilding = false;
			}
		}
		else {
			std::cout << "Successfully built the city. " << std::endl;
		}
	}

	std::cout << "Finished building the city. " << std::endl;
	
}

void Game::autoBuildCity(Player* player) {

	//Get the vertices where you have armies deployed
	vector<Vertex*> validVertices;
	for (int i = 0; i < map->vertices().size(); i++) {
		Vertex* currVertex = map->vertices().at(i);
		if (currVertex->getTerritory()->getArmiesByPlayer(player->getPlayerName()) > 0) {
			validVertices.push_back(currVertex);
		}
	}

	if (validVertices.size() == 0) {
		std::cout << "You do not have any regions with armies! " << std::endl;
		return;
	}

	Vertex* buildVertex = validVertices.at(0);

	try {
		//We build 1 city at a time only
		player->BuildCity(buildVertex, 1);
	}
	catch (PlayerActionException& ex) {
		std::cout << ex.what() << std::endl;
	}

	std::cout << "Finished building the city. " << std::endl;

}

void Game::DestroyArmies(Player* currPlayer, int detroyLimit) {
	bool destroyMoreArmies = true;
	while (detroyLimit > 0 && destroyMoreArmies) {

		Player* opponent = players.at(_getPlayerIndexFromUserInput("Please select the player to destroy armies:"));

		//Get the vertices where the opponent player has some armies deployed
		vector<Vertex*> destroyableVertices = opponent->GetDeployedVertices();

		std::cout << "\nRemaining armies can be destroyed: " << detroyLimit << std::endl;

		//Let the user select a vertex
		if (destroyableVertices.size() == 0) {
			std::cout << "There is no regions to be destroyed! " << std::endl;
			return;
		}

		Vertex* chosenVertex = destroyableVertices.at(_getVertexIndexFromUserInput(destroyableVertices, "Select the territory you would like to destroy armies in: "));

		//Let the user select how many armies to deploy
		int armiesToDestroy = _getArmiesForOperation(detroyLimit);

		try {
			currPlayer->DestroyArmy(chosenVertex, opponent, armiesToDestroy);
			detroyLimit -= armiesToDestroy;
			std::cout << "Armies destroyed successfully." << std::endl;
		}
		catch (PlayerActionException& ex) {
			std::cout << ex.what() << std::endl;
		}

		//Ask the player if he wants to continue
		if (detroyLimit > 0) {
			std::cout << "Do you want to continue destroying armies? (Y/N) ";
			if (!confirm()) {
				destroyMoreArmies = false;
			}
		}
		else {
			std::cout << "No more army destruction allowed. Out of moves. " << std::endl;
		}
	}
	std::cout << "Finish destroying armies." << std::endl;
}

void Game::autoDestroyArmies(Player* currPlayer, int detroyLimit) {

	Player* opponent = players.at(0);

	//Get the vertices where the opponent player has some armies deployed
	vector<Vertex*> destroyableVertices = opponent->GetDeployedVertices();

	std::cout << "\nRemaining armies can be destroyed: " << detroyLimit << std::endl;

	if (destroyableVertices.size() == 0) {
		std::cout << "There is no regions to be destroyed! " << std::endl;
		return;
	}

	//Destroy the first possible army
	Vertex* chosenVertex = destroyableVertices.at(0);

	//Destroy 1 army at a time
	int armiesToDestroy = 1;

	try {
		currPlayer->DestroyArmy(chosenVertex, opponent, armiesToDestroy);
		detroyLimit -= armiesToDestroy;
		std::cout << "Armies destroyed successfully." << std::endl;
	}
	catch (PlayerActionException& ex) {
		std::cout << ex.what() << std::endl;
	}

	std::cout << "Finish destroying armies." << std::endl;
}

int Game::_getVertexIndexFromUserInput(vector<Vertex*> vertices, std::string prompt) {

	displayTerritories(vertices, true);

	int vertexIndex = -1;
	do {
		std::cout << prompt;
		std::cin >> vertexIndex;
		if (vertexIndex < 0 || vertexIndex > vertices.size())
			std::cout << "Invalid option. Try again." << std::endl;
	} while (vertexIndex < 0 || vertexIndex > vertices.size());
	
	return vertexIndex;
}

int Game::_getArmiesForOperation(int limit) {
	//Let the user select how many armies to move
	int numOfArmies;
	do {
		std::cout << "Enter the number of armies. Must be less than or equal to " << limit << ": ";
		std::cin >> numOfArmies;
		if (numOfArmies < 0 || numOfArmies > limit)
			std::cout << "Invalid number of armies. Number of armies must be less than or equal to " << limit << std::endl;
	} while (numOfArmies < 0 || numOfArmies > limit);

	return numOfArmies;
}

int Game::_getPlayerIndexFromUserInput(std::string prompt) {
	for (int i = 0; i < players.size(); i++) {
		std::cout << (i + 1) << ". " << players.at(i) << std::endl;
	}

	int playerIndex = -1;
	do {
		std::cout << prompt;
		std::cin >> playerIndex; //This is the order from the list, starts with 1
		playerIndex -= 1;        //Convert it into index
		if (playerIndex < 0 || playerIndex > players.size())
			std::cout << "Invalid option. Try again." << std::endl;
	} while (playerIndex < 0 || playerIndex > players.size());

	return playerIndex;
}

void Game::notify() {
	//Recompute the score for each player before updating the observers
	for (int i=0; i<players.size(); i++)
		players.at(i)->ComputeScore(map, players);

	list<Observer*>::iterator observerIter;
	for (observerIter = _observers.begin(); observerIter != _observers.end(); observerIter++) {
		(**observerIter).update();
	}
}

//free functions
Vertex* Game::FindVertexById(Map* map, string id) {
	vector<Vertex*> vertices = map->vertices();
	for (vector<Vertex*>::iterator vertexIter = vertices.begin(); vertexIter != vertices.end(); vertexIter++) {
		if ((**vertexIter).getId().compare(id) == 0)
			return *vertexIter;
	}

	return nullptr;
}
