#pragma once
#include "../pch.h"
//#include "Player.h"
class Player;
class Game;
#include "../Cards/Cards.h"
#include "../GameCore/GameCore.h"

class Strategy {
public:
	Strategy();
	virtual Card* buyCard(Player* player, CardSpace& cardSpace, Deck& deck);
	virtual void performAction(Game* game, Player* player, Card* cardBeingPurchased);

	static Card* autoBuyCard(Player* player, CardSpace& cardSpace, Deck& deck, string strategy);
	static void autoPerformAction(Game* game, Player* player, Card* cardBeingPurchased, string strategy);
};

class HumanStrategy : public Strategy {
public:
	HumanStrategy();
	Card* buyCard(Player* player, CardSpace& cardSpace, Deck& deck);
	void performAction(Game* game, Player* player, Card* cardBeingPurchased);
};

class GreedyStrategy : public Strategy {
public:
	GreedyStrategy();
	Card* buyCard(Player* player, CardSpace& cardSpace, Deck& deck);
	void performAction(Game* game, Player* player, Card* cardBeingPurchased);
};

class ModerateStrategy : public Strategy {
public:
	ModerateStrategy();
	Card* buyCard(Player* player, CardSpace& cardSpace, Deck& deck);
	void performAction(Game* game, Player* player, Card* cardBeingPurchased);
};



