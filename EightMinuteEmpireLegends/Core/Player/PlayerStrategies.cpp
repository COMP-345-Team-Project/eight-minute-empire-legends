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

	std::cout << "\nCard Exchange Phase for Player " << player->getPlayerName() << "(Human Action)" << endl;

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

Card* GreedyStrategy::buyCard(Player* player, CardSpace& cardSpace, Deck& deck) {
	Card* cardBeingPurchased = autoBuyCard(player, cardSpace, deck, "Greedy");
	return cardBeingPurchased;
}

void GreedyStrategy::performAction(Game* game, Player* player, Card* cardBeingPurchased) {
	autoPerformAction(game, player, cardBeingPurchased, "Greedy");
}



Card* ModerateStrategy::buyCard(Player* player, CardSpace& cardSpace, Deck& deck) {
	Card* cardBeingPurchased = autoBuyCard(player, cardSpace, deck, "Moderate");
	return cardBeingPurchased;
}

void ModerateStrategy::performAction(Game* game, Player* player, Card* cardBeingPurchased) {
	autoPerformAction(game, player, cardBeingPurchased, "Moderate");
}



Card* Strategy::autoBuyCard(Player* player, CardSpace& cardSpace, Deck& deck, string strategy) {

	//Print out current cardSpace
	std::cout << "\nCard Exchange Phase for Player " << player->getPlayerName() << "(Automated Action)" << endl;
	cardSpace.showCardSpace();
	std::cout << "You have " << player->getCoins() << " coins available" << endl;

	int cardIndex = 0;

	//Loop through cardSpace to find the suitable card for Greedy and Moderate strategy
	for (int i = 0; i < cardSpace.getSize(); i++) {
		if (strategy == "Greedy") {
			if ((cardSpace.getCards()[i]->getFirstAction() == "buildCity" || cardSpace.getCards()[i]->getFirstAction() == "destroyArmy") && cardSpace.costCalc(i) <= player->getCoins()) {
				cardIndex = i;
				break;
			}
		}
		else {
			if ((cardSpace.getCards()[i]->getFirstAction() == "newArmy" || cardSpace.getCards()[i]->getFirstAction() == "moveArmy") && cardSpace.costCalc(i) <= player->getCoins()) {
				cardIndex = i;
				break;
			}
		}
	}

	//Making Card Purchase
	Card* cardBeingPurchased = cardSpace.sell(deck, cardIndex+1);
	player->BuyCard(cardBeingPurchased, cardSpace.costCalc(cardIndex));

	//Print coin balance
	std::cout << "Card cost: " << cardSpace.costCalc(cardIndex) << endl;
	std::cout << "You have " << player->getCoins() << " coins left after card purchase" << endl;

	return cardBeingPurchased;
}

void Strategy::autoPerformAction(Game* game, Player* player, Card* cardBeingPurchased, string strategy) {
	
	Game::_listActions(cardBeingPurchased);

	//game->_performAction(cardBeingPurchased, player, 1);
	
	//Performing first action
	if (cardBeingPurchased->getFirstAction() == "newArmy") {
		//game->PlaceArmies(player, cardBeingPurchased->getNewArmy());
		game->autoPlaceArmies(player, cardBeingPurchased->getNewArmy());
	}
	else if (cardBeingPurchased->getFirstAction() == "moveArmy") {
		game->autoMoveArmies(player, cardBeingPurchased->getMoveArmy());
	}
	else if (cardBeingPurchased->getFirstAction() == "buildCity") {
		game->autoBuildCity(player);
	}
	else if (cardBeingPurchased->getFirstAction() == "destroyArmy") {
		game->autoDestroyArmies(player, cardBeingPurchased->getDestroyArmy());
	}
	else {
		std::cout << "Unknown action"<< endl;
	}

	//Performing second action if available
	if (cardBeingPurchased->getAndAction()) {

		if (cardBeingPurchased->getSecondAction() == "newArmy") {
			game->autoPlaceArmies(player, cardBeingPurchased->getNewArmy());
		}
		else if (cardBeingPurchased->getSecondAction() == "moveArmy") {
			game->autoMoveArmies(player, cardBeingPurchased->getMoveArmy());
		}
		else if (cardBeingPurchased->getSecondAction() == "buildCity") {
			game->autoBuildCity(player);
		}
		else if (cardBeingPurchased->getSecondAction() == "destroyArmy") {
			game->autoDestroyArmies(player, cardBeingPurchased->getDestroyArmy());
		}
		else {
			std::cout << "Unknown action" << endl;
		}
	}

}


