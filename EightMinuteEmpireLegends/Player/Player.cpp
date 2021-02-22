#include <iostream>
#include "Player.h"

Player::Player(std::string name, Deck deck, BidTieBreaker& bidTieBreaker) : playerName(name), coin(14), hand(deck), biddingFacility(bidTieBreaker) {}

Player::~Player() {}

void Player::payCoin() {
	std::cout << "Entered payCoin method" << std::endl;
}

void Player::PlaceNewArmies() {
	std::cout << "Entered PlaceNewArmies method" << std::endl;
}

void Player::MoveArmies() {
	std::cout << "Entered MoveArmies method" << std::endl;
}

void Player::MoveOverLand() {
	std::cout << "Entered MoveOverLand method" << std::endl;
}

void Player::BuildCity() {
	std::cout << "Entered BuildCity method" << std::endl;
}

void Player::DestroyArmy() {
	std::cout << "Entered DestroyArmy method" << std::endl;
}
