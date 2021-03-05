#include "PlayerTests.h"

int PlayerTests::Test_PlayerFunctionsExecute()
{
	Deck deck(2);
	BidTieBreakerByLastName bidTieBreakerByLastName;
	Player* p1 = new Player("player1", deck, bidTieBreakerByLastName);

	p1->BuildCity();
	p1->DestroyArmy();
	p1->MoveArmies();
	p1->MoveOverLand();
	p1->payCoin();
	p1->PlaceNewArmies();

	delete p1;
	return 0;
}
