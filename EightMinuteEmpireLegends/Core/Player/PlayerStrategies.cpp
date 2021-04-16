#pragma once
#include "../pch.h"
#include "PlayerStrategies.h"
#include "Player.h"
#include "../Cards/Cards.h"
#include "../GameCore/GameCore.h"

Strategy::Strategy() {}

HumanStrategy::HumanStrategy() {}

GreedyStrategy::GreedyStrategy() {}

ModerateStrategy::ModerateStrategy() {}


Card* Strategy::buyCard(Player* player, CardSpace& cardSpace, Deck& deck) {
	std::cout << "BaseClass buyCard()" << std::endl; //For Debug
	return (new Card());
}

void Strategy::performAction(Game* game, Player* player, Card* cardBeingPurchased) {
	std::cout << "BaseClass performAction()" << std::endl; //For Debug
}

Card* HumanStrategy::buyCard(Player* player, CardSpace& cardSpace, Deck& deck) {
	
	int cardInput = 1; //Position from user input

	std::cout << "\nCard Exchange Phase for Player " << player->getPlayerName() << endl;

	//Getting user input to buy cards
	cardSpace.showCardSpace();

	cout << "You have " << player->getCoins() << " coins available" << endl;

	cout << "Choose which card you'd like to buy from Card Space (1-6): ";
	cin >> cardInput;

	if (cardInput > 0 && cardInput < (cardSpace.getSize() + 1) && player->getCoins() >= cardSpace.costCalc(cardInput - 1)) {
		std::cout << "Card " << cardInput << " Successfully bought" << endl;
	}
	else if (cardInput > 0 && player->getCoins() < cardSpace.costCalc(cardInput - 1)) {
		std::cout << "!Not enough coins! Default to first free card. \n"; //Exception handler
		cardInput = 1;
	}
	else {
		std::cout << "!invalid selection! Default to first free card. \n";
		cardInput = 1;
	}
	Card* cardBeingPurchased = cardSpace.sell(deck, cardInput);
	//Make the card purchase
	player->BuyCard(cardBeingPurchased, cardSpace.costCalc(cardInput - 1));

	//Print coin balance
	std::cout << "Card cost: " << cardSpace.costCalc(cardInput - 1) << endl;
	std::cout << "You have " << player->getCoins() << " coins left after card purchase" << endl;

	return cardBeingPurchased;
}

void HumanStrategy::performAction(Game* game, Player* player, Card* cardBeingPurchased) {
	
	//We have an option to skip the action 
	Game::_listActions(cardBeingPurchased);

	//If there are 2 actions
	if (cardBeingPurchased->getSecondAction().compare("") != 0) {
		//And actions
		if (cardBeingPurchased->getAndAction()) {
			game->_performAction(cardBeingPurchased, player, 1);
			game->_performAction(cardBeingPurchased, player, 2);
		}
		//Or actions
		else {
			int option = -1;
			do {
				//We need to perform type checking somehow... to be implemented later
				std::cin >> option;
				if (option < 1 || option > 2) {
					std::cout << "Invalid action option, please try again." << std::endl;
				}
			} while (option < 1 || option > 2);

			game->_performAction(cardBeingPurchased, player, option);
		}
	}
	else {
		//We only have 1 option
		game->_performAction(cardBeingPurchased, player, 1);
	}
	
}

void GreedyStrategy::buyCard(Player* player, CardSpace& cardSpace) {
	autoBuyCard(cardSpace, "Greedy");
}

void GreedyStrategy::performAction() {
	std::cout << "Greedy performAction()" << std::endl;
}

void ModerateStrategy::buyCard(Player* player, CardSpace& cardSpace) {
	std::cout << "Moderate buyCard()" << std::endl;
}

void ModerateStrategy::performAction() {
	std::cout << "Moderate buyCard()" << std::endl;
}

Card* Strategy::autoBuyCard(CardSpace& cardSpace, string strategy) {
	std::cout << "Strategy: " << strategy << endl;
	cardSpace.showCardSpace();

	return new Card();
}


