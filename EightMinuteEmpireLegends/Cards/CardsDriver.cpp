#include "Cards.h"

#include <iostream>
#include <vector>

#include <algorithm>    // std::random_shuffle
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
using namespace std;

int main() {


    cout << "This is the cards driver!\n";

	// Assuming there are 3 players
    int numPlayer = 3;
	cout << "Assuming a 3 players game" << endl;

	/*
    while (numPlayer < 2 or numPlayer > 4) {
        cout << "How many players are present? (2-4) \n";
        cin >> numPlayer;
    }
	*/

    //Deck reveal() is included to demo deck functionality, NOT included in actual game

    //Demo deck
    Deck testDeck(numPlayer);
    testDeck.reveal();

    //Demo hand
    Hand testHand(testDeck);

    //Demo exchange cards until both Deck and Hand are emptry
    while (testHand.getSize() > 0) {
        testHand.exchange(testDeck, true); //Invoked demo mode here to automate all user interaction
        testDeck.reveal();
    }
    cout << "Hand has been depleted, demo ends" << endl;

}
