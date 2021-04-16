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
	static Card* autoBuyCard(CardSpace& cardSpace, string strategy);
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
	void buyCard(Player* player, CardSpace& cardSpace);
	void performAction();
};

class ModerateStrategy : public Strategy {
public:
	ModerateStrategy();
	void buyCard(Player* player, CardSpace& cardSpace);
	void performAction();
};



