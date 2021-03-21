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


void Player::PayCoin(int coins) {
	std::cout << "Entered payCoin method" << std::endl;
}

void Player::PlaceNewArmies(Map* map, Vertex* v, int numOfArmies) {
	std::cout << "Entered PlaceNewArmies method" << std::endl;
}

void Player::MoveArmies(Map* map, Vertex* from, Vertex* to, int numOfArmies, int& remainingMoves) {
	std::cout << "Entered MoveArmies method" << std::endl;
}

void Player::DestroyArmy(Vertex* v, int numOfArmies) {
	std::cout << "Entered BuildCity method" << std::endl;
}

void Player::BuildCity(Vertex* v, int numOfArmies) {
	std::cout << "Entered BuildCity method" << std::endl;
}

void Player::InitResources(int coin, int armies, int cities) {
	this->coin = coin;
	this->availableArmies = armies;
	this->availableCities = cities;
}
