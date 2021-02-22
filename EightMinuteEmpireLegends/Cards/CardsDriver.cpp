#include "Cards.h"

#include <iostream>
#include <vector>

#include <algorithm>    // std::random_shuffle
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
using namespace std;

int main() {


    cout << "This is the cards driver!\n";

    int numPlayer = 0;

    while (numPlayer < 2 or numPlayer > 4) {
        cout << "How many players are present? (2-4) \n";
        cin >> numPlayer;
    }

    //Deck reveal() is included to demo deck functionality, NOT included in actual game

    //Demo deck
    Deck testDeck(numPlayer);
    testDeck.reveal();

    //Demo hand
    Hand testHand(testDeck);

    //Demo exchange cards until both Deck and Hand are emptry
    while (testHand.getSize() > 0) {
        testHand.exchange(testDeck, false);
        testDeck.reveal();
    }
    cout << "Hand has been depleted, demo ends" << endl;

}
