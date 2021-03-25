#pragma once

#include "../pch.h"
#include "GameCore.h"

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

Game::Game(Resources& resources, Map& map, Deck& deck, vector<Player*> players) {
	this->resources = &resources;
	this->map = &map;
	this->deck = &deck;
	this->players = players;
}

Game::~Game() {

	delete resources, map, deck, players;
}
void Game::startUp() {

	if (players.size() == 2) {
		_placeArmies();
	}
	_assignResources();
	_bid();

	startGame();
}

void Game::_placeArmies() {


	//Special Case for 2 players game
	if (players.size() == 2) {

		std::cout << "!! 2 Player special cases to be implemented !!\n" << endl;

		///////////////////////////////////////////
		////
		////          2 Player's special action
		////        
		////
		///////////////////////////////////////////
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

void Game::startGame() {


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

			//Make the card purchase
			players[i]->buyCard(cardSpace.sell(*deck, cardInput), cardSpace.costCalc(cardInput - 1));


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
	endGame();
}

void Game::endGame() {

	std::cout << "!End game block!" << endl;
}


Game* GameBuilder::build(int numPlayers, Map& map, std::string path) {
	Resources rsc;

	// Initiallize resources if path to config is specified		
	if (path != "") {
	std::tuple<int, int, int> tResources;
	try {
			tResources = fetchConfigResources(path);
			rsc = Resources(std::get<0>(tResources), std::get<1>(tResources), std::get<2>(tResources));
	}
		catch (ConfigFileException& e) {
		std::cout << "Uh oh! Configuration file not found. Resources will use default values." << std::endl << e.what() << std::endl;
		tResources = std::make_tuple(_dCoins, _dArmies, _dCities);
	}
	}
	else {
		
		//Initiallize resources to default parameters if path to config is not specified
		rsc = Resources();
	}
		
	Deck deck = Deck(numPlayers);
	BidTieBreakerByLastName tieBreaker;
	vector<Player*> pl{};
	for (int i = 1; i <= numPlayers; i++) {
		BiddingFacility bf(tieBreaker);
		pl.push_back(new Player("Player " + i));
	}

	//Crete a new game object and pass above objects to Game
	return new Game(rsc, map, deck, pl);
}


Game* GameBuilder::buildGame(int numPlayers, Map& map) {
	
	string playerName;

	Resources rsc = Resources();
	vector<Player*> players;

	for (int i = 0; i < numPlayers; i++) {
		//Player Creation
		std::cout << "Please enter the Last Name for Player " << i + 1 << ": ";
		std::cin >> playerName;

		players.push_back(new Player(playerName));
	}

	//Creating a deck
	Deck* deck = new Deck(numPlayers);

	//Crete a new game object and pass above objects to Game
	return new Game(rsc, map, *deck, players);
}


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