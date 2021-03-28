#pragma once

#include "CardsTests.h"

#include "../../Core/Cards/Cards.h"

int CardsTests::Test_CanBuildDeckAndHand_Demo()
{
	std::cout << "This is the cards driver!" << std::endl;

	// Assuming there are 3 players
	int numPlayer = 3;
	std::cout << "Assuming a 3 players game" << std::endl;

	//Deck reveal() is included to demo deck functionality, NOT included in actual game
	//Demo deck
	Deck testDeck(numPlayer);
	testDeck.reveal();

	//Demo CardSpace
	CardSpace testCardSpace(testDeck);

	//Demo exchange cards until both Deck and CardSpace are emptry
	while (testCardSpace.getSize() > 0) {
		testCardSpace.exchange(testDeck, true); //Invoked demo mode here to automate all user interaction
		testDeck.reveal();
	}
	std::cout << "CardSpace has been depleted, demo ends" << std::endl;

	return 0;
}
