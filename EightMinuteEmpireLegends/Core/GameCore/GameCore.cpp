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

Game::Game(Resources& resources, Map& map, Deck& deck, vector<Player*> players) {
	this->resources = &resources;
	this->map = &map;
	this->deck = &deck;
	this->players = players;
}

Game::~Game() {
	delete this->map;
	for (Player* pl : this->players) {
		delete pl;
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

void Game::displayTerritories(std::vector<Vertex*> vertices) {
	for (Vertex* v : vertices) {		
		std::cout << "Territory : " << v->getTerritory()->getName() << std::endl;
		std::cout << "Owner     : " << v->getTerritory()->getOwner() << std::endl;
		std::cout << "Continent : " << v->getTerritory()->getContinent() << std::endl;
		std::cout << "--- Armies ---" << std::endl;
		for (Player* pl : this->getPlayers()) {
			std::cout << pl->getPlayerName() << " - " << v->getTerritory()->getArmiesByPlayer(pl->getPlayerName()) << std::endl; 
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
	Resources rsc;
	Map* map = nullptr;

	// Initiallize resources if path to config is specified		
	if (configPath != "") {
		std::tuple<int, int, int> tResources;
		try {
			tResources = fetchConfigResources(configPath);
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

	try {
		map = MapLoader::parseMap(mapPath);
	}
	catch (MapLoaderException& e) {
		std::cout << e.what() << std::endl;		
	}

	Deck deck = Deck(numPlayers);
	BidTieBreakerByLastName tieBreaker;
	BiddingFacility* bf = new BiddingFacility(tieBreaker);
	std::vector<Player*> pl{};
	for (int i = 0; i < numPlayers; i++) {
		pl.push_back(new Player(names.at(i), bf));
	}

	//Crete a new game object and pass above objects to Game
	return new Game(rsc, *map, deck, pl);
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