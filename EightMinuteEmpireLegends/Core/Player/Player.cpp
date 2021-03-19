#pragma once
#include "../pch.h"

#include "Player.h"

Player::Player(std::string name, Deck deck, BidTieBreaker& bidTieBreaker) : playerName(name), coin(14), hand(deck), biddingFacility(bidTieBreaker) {}

Player::~Player() {}

void Player::PayCoin(int coins) {
	std::cout << "Entered payCoin method" << std::endl;
}

void Player::PlaceNewArmies(Vertex v, int numOfArmies) {
	std::cout << "Entered PlaceNewArmies method" << std::endl;
}

void Player::MoveArmies(Vertex from, Vertex to, int numOfArmies) {
	std::cout << "Entered MoveArmies method" << std::endl;
}

void Player::DestroyArmy(Vertex v, int numOfArmies) {
	std::cout << "Entered BuildCity method" << std::endl;
}

void Player::BuildCity(Vertex v, int numOfArmies) {
	std::cout << "Entered BuildCity method" << std::endl;
}

void Player::InitResources(int coin, int armies, int cities) {
	std::cout << "Entered DestroyArmy method" << std::endl;
}
