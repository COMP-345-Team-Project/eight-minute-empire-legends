#pragma once
#include "../pch.h"
#include "GameCore.h"

const int _dCoins = 36;
const int _dArmies = 18;
const int _dCities = 3;

Resources::Resources() {
	this->coins = 36;
	this->armies = 18;
	this->cities = 3;
}

Resources::Resources(int coins, int armies, int cities) {
	this->coins = coins;
	this->armies = armies;
	this->cities = cities;
}

void Resources::assignInitialResources(vector<Player*> players) {
	for (Player* pl : players) {
		// Assign resources to players
	}
}

Game::Game(Resources& resources, Map& map, Deck& deck, vector<Player*> players) {
	this->resources = &resources;
	this->map = &map;
	this->deck = &deck;
	this->players = players;
}

Game* GameBuilder::build(int numPlayers, Map& map) {
	std::tuple<int, int, int> tResources;
	try {
		tResources = fetchConfigResources("../../../config/EightMinuteEmpireLengendsPrefs.ini");
	}
	catch (std::exception& e) {
		std::cout << "Uh oh! Configuration file not found. Resources will use default values." << std::endl << e.what() << std::endl;
		tResources = std::make_tuple(_dCoins, _dArmies, _dCities);
	}
		
	Deck deck = Deck(numPlayers);
	BidTieBreakerByLastName tieBreaker;
	vector<Player*> pl{};
	for (int i = 1; i <= numPlayers; i++) {
		BiddingFacility bf(tieBreaker);
		pl.push_back(new Player("Player " + i, deck, bf));
	}

	//Initiallize resources via constructor
	Resources rsc = Resources(std::get<0>(tResources), std::get<1>(tResources), std::get<2>(tResources));

	//Crete a new game object and pass above objects to Game
	return new Game(rsc, map, deck, pl);
}

std::tuple<int, int, int> fetchConfigResources(std::string path) {
	int coins;
	int armies;
	int cities;
	std::string line;
	char delim = '=';
	std::ifstream rFile(path);
	if (rFile.is_open()) {
		while (getline(rFile, line, delim)) {
			std::vector<std::string> ln{};
			ln.push_back(line);
			if (ln.size() > 1 && ln[0] == "rCoins") {
				coins = std::stoi(ln[1]);
			}
			if (ln.size() > 1 && ln[0] == "rArmies") {
				armies = std::stoi(ln[1]);
			}
			if (ln.size() > 1 && ln[0] == "rCities") {
				cities = std::stoi(ln[1]);
			}
		}
	}
	return std::make_tuple(cities, armies, cities);
}