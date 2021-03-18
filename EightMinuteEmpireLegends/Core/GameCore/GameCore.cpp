#pragma once
#include "../pch.h"
#include "GameCore.h"

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
/*
Game GameBuilder::build(int numPlayers, Map& map) {

}*/