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
		pl.push_back(new Player("Player " + i, deck, bf));
	}	

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