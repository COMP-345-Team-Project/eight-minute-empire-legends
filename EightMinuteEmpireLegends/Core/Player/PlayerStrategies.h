#include "../pch.h"
//#include "Player.h"

class Strategy {
public:
	Strategy();
	void virtual buyCard();
	void virtual performAction();
};

class HumanStrategy : public Strategy {
public:
	HumanStrategy();
	void buyCard();
	void performAction();
};

class GreedyStrategy : public Strategy {
public:
	GreedyStrategy();
	void buyCard();
	void performAction();
};

class ModerateStrategy : public Strategy {
public:
	ModerateStrategy();
	void buyCard();
	void performAction();
};



