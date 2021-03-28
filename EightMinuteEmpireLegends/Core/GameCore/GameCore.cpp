#pragma once

#include "../pch.h"
#include "GameCore.h"

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

std::ostream& operator <<(std::ostream& os, const Resources* r) {
	os << "coins : " << r->coins << std::endl << "armies : " << r->armies << std::endl << "cities : " << r->cities;
	return os;
}

// Game class implementation.

Game::Game(Resources* resources, Map* map, Deck* deck, vector<Player*> players) {
	this->resources = resources;
	this->map = map;
	this->deck = deck;
	this->players = players;
	if (players.size() == 2) {
		this->neutralPlayer = new Player("NeutralPlayer", nullptr, true);
		neutralPlayer->InitResources(0, 10, 0);
	}
}

Game::Game() { //For testing only
	this->resources = NULL;
	this->map = NULL;
	this->deck = NULL;
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
	if (players.size() == 2) {
		Player* p1 = players.at(0);
		Player* p2 = players.at(1);
		
		//First we compare the scores
		int p1Score = p1->ComputeScore(map, players);
		int p2Score = p2->ComputeScore(map, players);

		if (p1Score > p2Score) {
			std::cout << "The winner is player: " << p1->getPlayerName() << std::endl;
			return;
		}
		else if (p1Score < p2Score) {
			std::cout << "The winner is player: " << p2->getPlayerName() << std::endl;
			return;
		}

		//If there is a tie, we compare the number of coins
		if (p1->getCoins() > p2->getCoins()) {
			std::cout << "The winner is player: " << p1->getPlayerName() << std::endl;
			return;
		}
		else if (p1->getCoins() < p2->getCoins()) {
			std::cout << "The winner is player: " << p2->getPlayerName() << std::endl;
			return;
		}

		//If there is a tie, we then compare the number of controlled regions
		int p1RegionScore = p1->ComputeTerritoryScore();
		int p2RegionScore = p2->ComputeTerritoryScore();

		if (p1RegionScore > p2RegionScore) {
			std::cout << "The winner is player: " << p1->getPlayerName() << std::endl;
			return;
		}
		else if (p1RegionScore < p2RegionScore) {
			std::cout << "The winner is player: " << p2->getPlayerName() << std::endl;
			return;
		}

		std::cout << " This game is a tie!" << std::endl;
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
	for (Player* pl : g->players) {
		os << pl << std::endl;
	}	
	return os;
}

// Startup Phase

void Game::runSetupPhase() {
	_assignResources();
	_bid();
	_placeArmies();
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








void Game::runRoundsUntilEndGame() {


	//Creating a CardSpace
	CardSpace cardSpace = CardSpace(*deck);

	//Game ends when each players have certain numbers of cards
	int endGameCardCount = 13;
	if (players.size() == 3) {
		endGameCardCount = 10;
	}
	if (players.size() == 4) {
		endGameCardCount = 8;
	}

	int gameRound = 1;

	//Main loop until game ends
	//End game condition
	while (players[players.size() - 1]->getCards().size() < endGameCardCount) {

		std::cout << "\n\nRound " << gameRound++ << endl;

		for (int i = 0; i < players.size(); i++) {

			int cardInput = 1; //Position from user input

			std::cout << "Card Exchange Phase for Player " << i + 1 << ": " << players[i]->getPlayerName() << endl;

			//Getting user input to buy cards
			cardSpace.showCardSpace();

			cout << "You have " << players[i]->getCoins() << " coins available" << endl;

			cout << "Choose which card you'd like to buy from Card Space (1-6): ";
			cin >> cardInput;

			if (cardInput > 0 && cardInput < (cardSpace.getSize() + 1) && players[i]->getCoins() >= cardSpace.costCalc(cardInput - 1)) {
				std::cout << "Card " << cardInput << " Successfully bought" << endl;
			}
			else if (cardInput > 0 && players[i]->getCoins() < cardSpace.costCalc(cardInput - 1)) {
				std::cout << "!Not enough coins! Default to first free card. \n"; //Exception handler
				cardInput = 1;
			}
			else {
				std::cout << "!invalid selection! Default to first free card. \n";
				cardInput = 1;
			}
			Card* cardBeingPurchased = cardSpace.sell(*deck, cardInput);
			//Make the card purchase
			players[i]->BuyCard(cardBeingPurchased, cardSpace.costCalc(cardInput - 1));


			//Print coin balance
			std::cout << "Card cost: " << cardSpace.costCalc(cardInput - 1) << endl;
			std::cout << "You have " << players[i]->getCoins() << " coins left after card purchase" << endl;

			//Perform action on bought card
			std::cout << "Do you want to perform the card actions?" << endl;

			///////////////////////////////////////////
			////
			////          Player's action block
			////          players[i] gives you access to the current player
			////
			///////////////////////////////////////////


		}

	}
}


// Gamebuilder class implementation. 

Game* GameBuilder::build() {
	std::vector<filesystem::path> maps = fetchMapFiles(_mapDir);
	std::vector<std::string> names{};
	std::cout << "Please select a map.\n" << std::endl;
	int index = 0;
	int mapSelection;
	int numPlayers;

	// Map selection
	for (const auto& entry : maps) {		
		std::cout << index << ") " << entry.filename() << std::endl;
		index++;
	}
	std::cin >> mapSelection;
	if (mapSelection < 0 || mapSelection >= maps.size()) {
		throw GameBuilderException("ERR: Selection index out of range.");
	}	

	// Player selection
	
	bool validNum = false;	
	while (!validNum) {		
		std::cout << "Please enter the number of players (2-4) : ";
		std::cin >> numPlayers;
		if (cin.fail()) {
			cin.clear();
			cin.sync();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input. Please enter an integer.\n" << std::endl;
		}
		else if (numPlayers < 2 || numPlayers > 4) {
			std::cout << "Player count selection out of range.\n" << std::endl;
		}
		else {
			validNum = true;
		}
	}	
	std::string plName;
	bool validName;
	for (int i = 0; i < numPlayers; i++) {
		validName = false;
		while (!validName) {			
			std::cout << "Please enter a name for player " + i << " : ";
			std::cin >> plName;			
			if (std::find(names.begin(), names.end(), plName) != names.end()) {
				std::cout << "Name has already been taken by another player. Please enter a unique name." << std::endl;
			}
			else {
				validName = true;
			}
		}
		names.push_back(plName);
	}

	return build(numPlayers, names, maps.at(mapSelection).u8string(), _configPath);
}

Game* GameBuilder::build(int numPlayers, std::vector<std::string> names, std::string mapPath, std::string configPath) {
	Resources* rsc = nullptr;
	Map* map = nullptr;

	// Initiallize resources if path to config is specified		
	if (configPath != "") {
		std::tuple<int, int, int> tResources;
		try {
			tResources = fetchConfigResources(configPath);
			rsc = new Resources(std::get<0>(tResources), std::get<1>(tResources), std::get<2>(tResources));
		}
		catch (ConfigFileException& e) {
			std::cout << "Uh oh! Configuration file not found. Resources will use default values." << std::endl << e.what() << std::endl;
			tResources = std::make_tuple(_dCoins, _dArmies, _dCities);
		}
	}
	else {
		//Initiallize resources to default parameters if path to config is not specified
		rsc = new Resources();
	}

	try {
		map = MapLoader::parseMap(mapPath);
	}
	catch (MapLoaderException& e) {
		std::cout << e.what() << std::endl;		
	}

	Deck* deck = new Deck(numPlayers);
	BidTieBreakerByLastName tieBreaker;
	BiddingFacility* bf = new BiddingFacility(tieBreaker);
	std::vector<Player*> pl{};
	for (int i = 0; i < numPlayers; i++) {
		pl.push_back(new Player(names.at(i), bf));
	}

	//Crete a new game object and pass above objects to Game
	return new Game(rsc, map, deck, pl);
}

// Helper function. Reads resources from config file.
std::tuple<int, int, int> fetchConfigResources(std::string path) {
	int coins;
	int armies;
	int cities;
	std::string line;
	char delim = '=';
	std::ifstream rFile(path);
	if (rFile.is_open()) {
		while (getline(rFile, line)) {
			if (line.substr(0, line.find(delim)) == "rCoins") {
				coins = std::stoi(line.substr(line.find(delim) + 1));
			}
			if (line.substr(0, line.find(delim)) == "rArmies") {
				armies = std::stoi(line.substr(line.find(delim) + 1));
			}
			if (line.substr(0, line.find(delim)) == "rCities") {
				cities = std::stoi(line.substr(line.find(delim) + 1));
			}
		}
		rFile.close();
	}
	else {
		throw ConfigFileException("ERR: Unable to open file at " + path);
	}
	return std::make_tuple(coins, armies, cities);;
}

std::vector<filesystem::path> fetchMapFiles(std::string path) {
	std::vector<filesystem::path> maps{};	
	for (const auto& entry : filesystem::directory_iterator(path)) {
		maps.push_back(entry.path());		
	}
	return maps;
}