<<<<<<< Updated upstream
#include "Cards.h"

#include <iostream>
#include <vector>

#include <algorithm>    // std::random_shuffle
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
using namespace std;

Card::Card(string nameValue, int newArmyValue, int moveArmyValue, int buildCityValue, int destroyArmyValue,
    string firstActionValue, string secondActionValue, bool andActionValue, int extraMoveValue,
    int extraArmyValue, bool flyingValue, int elixerValue, int extraCoinValue, string specialAbilityValue) {
    name = nameValue;
    newArmy = newArmyValue;
    moveArmy = moveArmyValue;
    buildCity = buildCityValue;
    destroyArmy = destroyArmyValue;
    firstAction = firstActionValue; //Order must be dictated as the action must be taken sequencially
    secondAction = secondActionValue;
    andAction = andActionValue;
    extraMove = extraMoveValue;
    extraArmy = extraArmyValue;
    flying = flyingValue;
    elixer = elixerValue;
    extraCoin = extraCoinValue;
    specialAbility = specialAbilityValue;
}

Card::Card() {
    name = "";
    newArmy = 0;
    moveArmy = 0;
    buildCity = 0;
    destroyArmy = 0;
    firstAction = "";
    secondAction = "";
    andAction = false;
    extraMove = 0;
    extraArmy = 0;
    flying = false;
    elixer = 0;
    extraCoin = 0;
    specialAbility = "";

}

//Print out card's attributes
void Card::print() {
    //Card's Action
    cout << name << " (Action: ";
    printHelper(firstAction);

    //Some cards have 2 actions, either AND or OR
    if (secondAction != "") {
        if (andAction == true) {
            cout << "AND ";
        }
        else {
            cout << "OR ";
        }

        printHelper(secondAction);
    }
    cout << ") ";

    //Card's Ability
    if (extraMove != 0 || extraArmy != 0 || flying == true || elixer != 0 || extraCoin != 0) {
        cout << "(Ability: ";

        if (extraMove != 0) {
            cout << "Extra Move (" << extraMove << ") ";
        }
        if (extraArmy != 0) {
            cout << "Extra Army (" << extraArmy << ") ";
        }
        if (flying == true) {
            cout << "Flying ";
        }
        if (elixer != 0) {
            cout << "Elixer (" << elixer << ") ";
        }
        if (extraCoin != 0) {
            cout << "Extra Coin (" << extraCoin << ") ";
        }
        cout << ") ";
    }

    //Card's Special Ability
    if (specialAbility != "") {
        cout << "(Special Ability: " << specialAbility << ") ";
    }

    cout << "\n";

};

//Utility function for printing car's action string
void Card::printHelper(string str) {
    if (str == "newArmy") {
        cout << "New Army (" << newArmy << ") ";
    }
    else if (str == "moveArmy") {
        cout << "Move Army (" << moveArmy << ") ";
    }
    else if (str == "buildCity") {
        cout << "Build City (" << buildCity << ") ";
    }
    else {
        cout << "Destroy Army (" << destroyArmy << ") ";
    }
};

//Getter
string Card::getName() {
    return name;
}
int Card::getNewArmy() {
    return newArmy;
}
int Card::getMoveArmy() {
    return moveArmy;
}
int Card::getBuildCity() {
    return buildCity;
}
int Card::getDestroyArmy() {
    return destroyArmy;
}
string Card::getFirstAction() {
    return firstAction;
}
string Card::getSecondAction() {
    return secondAction;
}
bool Card::getAndAction() {
    return andAction;
}
int Card::getExtraMove() {
    return extraMove;
}
int Card::getExtraArmy() {
    return extraArmy;
}
bool Card::getFlying() {
    return flying;
}
int Card::getElixer() {
    return elixer;
}
int Card::getExtraCoin() {
    return extraCoin;
}
string Card::getSpecialAbility() {
    return specialAbility;
}




Deck::Deck() {

}

Deck::Deck(int numPlayer) {

    //Card cardSample("Sample", 0, 0, 0, 0, "", "", false, 0, 0, false, 0, 0, "");

    Card card1("Ancient Phoenix", 0, 5, 0, 0, "moveArmy", "", false, 0, 0, true, 0, 0, "");
    Card card2("Ancient Sage", 0, 3, 0, 0, "moveArmy", "", false, 0, 0, false, 0, 0, "1VPperAncient");
    Card card3("Ancient Tree Spirit", 4, 0, 0, 0, "newArmy", "", false, 0, 0, false, 3, 0, "");
    Card card4("Ancient Woods", 1, 0, 1, 0, "buildCity", "newArmy", true, 0, 1, false, 0, 0, "");
    Card card5("Cursed Banshee", 0, 6, 0, 0, "moveArmy", "", false, 0, 0, false, 2, 0, "");
    Card card6("Cursed Gargoyles", 0, 5, 0, 0, "moveArmy", "", false, 0, 0, true, 0, 0, "");
    Card card7("Cursed King", 3, 4, 0, 0, "newArmy", "moveArmy", false, 0, 0, false, 1, 0, "");
    Card card8("Cursed Mausoleum", 0, 0, 1, 0, "buildCity", "", false, 1, 0, false, 0, 0, "");
    Card card9("Cursed Tower", 0, 0, 1, 0, "buildCity", "", false, 0, 0, false, 0, 0, "1VPperFlying");
    Card card10("Dire Dragon", 3, 0, 0, 1, "newArmy", "destroyArmy", true, 0, 0, true, 0, 0, "");
    Card card11("Dire Eye", 4, 0, 0, 0, "newArmy", "", false, 0, 0, true, 0, 0, "");
    Card card12("Dire Giant", 3, 0, 0, 1, "newArmy", "destroyArmy", true, 0, 0, false, 0, 0, "immuneToAttack");
    Card card13("Dire Goblin", 0, 5, 0, 0, "moveArmy", "", false, 0, 0, false, 1, 0, "");
    Card card14("Dire Ogre", 0, 2, 0, 0, "moveArmy", "", false, 0, 0, false, 0, 0, "1VPper3Coins");
    Card card15("Forest Elf", 3, 2, 0, 0, "newArmy", "moveArmy", false, 0, 1, false, 0, 0, "");
    Card card16("Forest Gnome", 0, 2, 0, 0, "moveArmy", "", false, 0, 0, false, 3, 0, "");
    Card card17("Forest Pixie", 0, 4, 0, 0, "moveArmy", "", false, 0, 1, false, 0, 0, "");
    Card card18("Forest Tree Town", 0, 0, 1, 0, "buildCity", "", false, 1, 0, false, 0, 0, "");
    Card card19("Graveyard", 2, 0, 0, 0, "newArmy", "", false, 0, 0, false, 0, 0, "1VPperCursedCard");
    Card card20("Lake", 2, 3, 0, 0, "newArmy", "moveArmy", false, 0, 0, false, 0, 0, "1VPperForestCard");
    Card card21("Night Hydra", 0, 5, 0, 1, "moveArmy", "destroyArmy", true, 0, 1, false, 0, 0, "");
    Card card22("Night Village", 0, 0, 1, 0, "buildCity", "", false, 0, 1, false, 0, 0, "");
    Card card23("Night Wizard", 3, 0, 0, 1, "newArmy", "destroyArmy", true, 0, 0, false, 0, 0, "1VPperNightCard");
    Card card24("Noble Hills", 3, 0, 0, 0, "newArmy", "", false, 0, 0, false, 0, 0, "3NobleCards=4VP");
    Card card25("Noble Knight", 4, 0, 0, 1, "newArmy", "destroyArmy", true, 1, 0, false, 0, 0, "");
    Card card26("Noble Unicorn", 1, 4, 0, 0, "moveArmy", "newArmy", true, 1, 0, false, 0, 0, "");
    Card card27("Stronghold", 0, 0, 1, 0, "buildCity", "", false, 0, 0, false, 0, 0, "1VPperDireCard");
    addCard(card1);
    addCard(card2);
    addCard(card3);
    addCard(card4);
    addCard(card5);
    addCard(card6);
    addCard(card7);
    addCard(card8);
    addCard(card9);
    addCard(card10);
    addCard(card11);
    addCard(card12);
    addCard(card13);
    addCard(card14);
    addCard(card15);
    addCard(card16);
    addCard(card17);
    addCard(card18);
    addCard(card19);
    addCard(card20);
    addCard(card21);
    addCard(card22);
    addCard(card23);
    addCard(card24);
    addCard(card25);
    addCard(card26);
    addCard(card27);

    //For more than 2 players
    if (numPlayer >= 3) {
        Card card28("Arcane Manticore", 4, 0, 0, 1, "newArmy", "destroyArmy", true, 1, 0, false, 0, 0, "");
        Card card29("Arcane Sphinx", 3, 4, 0, 0, "newArmy", "moveArmy", false, 0, 0, true, 0, 0, "");
        Card card30("Arcane Temple", 0, 3, 0, 0, "moveArmy", "", false, 0, 0, false, 0, 0, "1VPperArcaneCard");
        Card card31("Mountain Dwarf", 2, 0, 0, 1, "newArmy", "destroyArmy", true, 0, 0, false, 0, 0, "3VPfor2MountainCards");
        Card card32("Mountain Treasury", 0, 3, 0, 0, "moveArmy", "", false, 0, 0, false, 1, 2, "");
        addCard(card28);
        addCard(card29);
        addCard(card30);
        addCard(card31);
        addCard(card32);
    }

    if (numPlayer == 4) {
        Card card33("Castle", 3, 0, 1, 0, "newArmy", "buildCity", false, 0, 0, false, 1, 0, "");
        Card card34("Castle 2", 0, 3, 1, 0, "moveArmy", "buildCity", true, 0, 0, false, 1, 0, "");
        addCard(card33);
        addCard(card34);
    }

    //Shuffle the cards
    shuffle();
}

//Add cards into the deck
void Deck::addCard(Card newCard) {
    deck.push_back(newCard);
}

//Changing the index position of the cards in the deck using random number
void Deck::shuffle() {

    //http://www.cplusplus.com/reference/algorithm/random_shuffle/
    srand(unsigned(std::time(0)));
    random_shuffle(deck.begin(), deck.end());
    //random_shuffle(deck.begin(), deck.end(), int(time(0)));
}

//Debug function to reveals all cards in deck
void Deck::reveal() {
    cout << "!! This is a debug utility to reveals all cards in deck, cards will be drawn from the back !!" << endl;
    cout << "Current deck size: " << deck.size() << endl;
    for (unsigned i = 0; i < deck.size(); i++) {
        cout << (i + 1) << ". ";
        deck[i].print();
    }
    cout << "\n";
}

//Draw card from deck
Card Deck::draw() {

    if (deck.size() > 0) {
        Card tempCard = deck.back();
        cout << "The card drawn from deck is: " << deck.back().getName() << endl;
        deck.pop_back();
        return tempCard;
    }
    else { //If the deck is empty, the card being returned will be named "EMPTY"
        Card tempEmpty("EMPTY", 0, 0, 0, 0, "newArmy", "", false, 0, 0, false, 0, 0, "");
        return tempEmpty;
    }

}

//Getter
int Deck::getSize() {
    return deck.size();
}


//Hand is hardcoded to draw 6 cards from deck upon initialization
Hand::Hand(Deck& mainDeck) {

    addCard(mainDeck.draw());
    addCard(mainDeck.draw());
    addCard(mainDeck.draw());
    addCard(mainDeck.draw());
    addCard(mainDeck.draw());
    addCard(mainDeck.draw());
}

//Add new cards into the hand
void Hand::addCard(Card newCard) {
    hand.push_back(newCard);
}

//Print out all cards in Hand associated with their current cost for exchange
void Hand::showHand() {
    cout << "\n---Cards currently in Hand--- \n";

    for (unsigned i = 0; i < hand.size(); i++) {
        cout << "(Cost " << costCalc(i) << " coins) " << (i + 1) << ". ";
        hand[i].print();
    }
}

//Utility function for calculating cost of exchange dynamically besed on their current index position
int Hand::costCalc(int index) {
    if (index == 0) {
        return 0;
    }
    else if (index == 1 or index == 2) {
        return 1;
    }
    else if (index == 3 or index == 4) {
        return 2;
    }
    else {
        return 3;
    }

}

//Exchange function to allow player to buy cards from hand using coins
//showHand function included for demonstration
Card Hand::exchange(Deck& mainDeck) {
    int cardInput; //Position from user input
    int cardChoice; //Index position from hand vector
    Card cardChosen;

    if (hand.size() > 0) {
        showHand();
        cout << "Choose which card you'd like to exchange (1-6): " << endl;
        cin >> cardInput;

        if (cardInput > 0 && cardInput < (hand.size() + 1)) {
            cardChoice = cardInput - 1;
        }
        else {
            cout << "!invalid selection! Default to first free card. \n"; //Exception handler
            cardChoice = 0;
        }

        cardChosen = hand[cardChoice];

        cout << "The card you've selected to exchange is " << cardChosen.getName() << endl;

        //Remove the card chosen from Hand and move all cards after it to the left by 1 position
        for (int i = cardChoice; i < (hand.size() - 1); i++) {
            hand[i] = hand[i + 1];
        }
        //Remove the last now supposed to be emptry slot
        hand.pop_back();

        //Draw new card to place into the rightmost position
        Card cardAdded = mainDeck.draw();

        //Handle when the deck is empty
        if (cardAdded.getName() == "EMPTY") {
            cout << "No more new cards from deck" << endl;
        }
        else {
            addCard(cardAdded);
        }

        cout << "Here is the cards in Hand after the exchange" << endl;
        showHand();

        return cardChosen;
    }

    //Return card named "EMPTRY" when hand is empty
    else {
        Card tempEmpty("EMPTY", 0, 0, 0, 0, "newArmy", "", false, 0, 0, false, 0, 0, "");
        return tempEmpty;
    }


}

//Getter
int Hand::getSize() {
    return hand.size();
}


=======
#include "Cards.h"

#include <iostream>
#include <vector>

#include <algorithm>    // std::random_shuffle
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
using namespace std;

Card::Card(string nameValue, int newArmyValue, int moveArmyValue, int buildCityValue, int destroyArmyValue,
    string firstActionValue, string secondActionValue, bool andActionValue, int extraMoveValue,
    int extraArmyValue, bool flyingValue, int elixerValue, int extraCoinValue, string specialAbilityValue) {
    name = nameValue;
    newArmy = newArmyValue;
    moveArmy = moveArmyValue;
    buildCity = buildCityValue;
    destroyArmy = destroyArmyValue;
    firstAction = firstActionValue; //Order must be dictated as the action must be taken sequencially
    secondAction = secondActionValue;
    andAction = andActionValue;
    extraMove = extraMoveValue;
    extraArmy = extraArmyValue;
    flying = flyingValue;
    elixer = elixerValue;
    extraCoin = extraCoinValue;
    specialAbility = specialAbilityValue;
}

Card::Card() {
    name = "";
    newArmy = 0;
    moveArmy = 0;
    buildCity = 0;
    destroyArmy = 0;
    firstAction = "";
    secondAction = "";
    andAction = false;
    extraMove = 0;
    extraArmy = 0;
    flying = false;
    elixer = 0;
    extraCoin = 0;
    specialAbility = "";

}

//Print out card's attributes
void Card::print() {
    //Card's Action
    cout << name << " (Action: ";
    printHelper(firstAction);

    //Some cards have 2 actions, either AND or OR
    if (secondAction != "") {
        if (andAction == true) {
            cout << "AND ";
        }
        else {
            cout << "OR ";
        }

        printHelper(secondAction);
    }
    cout << ") ";

    //Card's Ability
    if (extraMove != 0 || extraArmy != 0 || flying == true || elixer != 0 || extraCoin != 0) {
        cout << "(Ability: ";

        if (extraMove != 0) {
            cout << "Extra Move (" << extraMove << ") ";
        }
        if (extraArmy != 0) {
            cout << "Extra Army (" << extraArmy << ") ";
        }
        if (flying == true) {
            cout << "Flying ";
        }
        if (elixer != 0) {
            cout << "Elixer (" << elixer << ") ";
        }
        if (extraCoin != 0) {
            cout << "Extra Coin (" << extraCoin << ") ";
        }
        cout << ") ";
    }

    //Card's Special Ability
    if (specialAbility != "") {
        cout << "(Special Ability: " << specialAbility << ") ";
    }

    cout << "\n";

};

//Utility function for printing car's action string
void Card::printHelper(string str) {
    if (str == "newArmy") {
        cout << "New Army (" << newArmy << ") ";
    }
    else if (str == "moveArmy") {
        cout << "Move Army (" << moveArmy << ") ";
    }
    else if (str == "buildCity") {
        cout << "Build City (" << buildCity << ") ";
    }
    else {
        cout << "Destroy Army (" << destroyArmy << ") ";
    }
};

//Getter
string Card::getName() {
    return name;
}
int Card::getNewArmy() {
    return newArmy;
}
int Card::getMoveArmy() {
    return moveArmy;
}
int Card::getBuildCity() {
    return buildCity;
}
int Card::getDestroyArmy() {
    return destroyArmy;
}
string Card::getFirstAction() {
    return firstAction;
}
string Card::getSecondAction() {
    return secondAction;
}
bool Card::getAndAction() {
    return andAction;
}
int Card::getExtraMove() {
    return extraMove;
}
int Card::getExtraArmy() {
    return extraArmy;
}
bool Card::getFlying() {
    return flying;
}
int Card::getElixer() {
    return elixer;
}
int Card::getExtraCoin() {
    return extraCoin;
}
string Card::getSpecialAbility() {
    return specialAbility;
}




Deck::Deck() {

}

Deck::Deck(int numPlayer) {

    //Card cardSample("Sample", 0, 0, 0, 0, "", "", false, 0, 0, false, 0, 0, "");

    Card card1("Ancient Phoenix", 0, 5, 0, 0, "moveArmy", "", false, 0, 0, true, 0, 0, "");
    Card card2("Ancient Sage", 0, 3, 0, 0, "moveArmy", "", false, 0, 0, false, 0, 0, "1VPperAncient");
    Card card3("Ancient Tree Spirit", 4, 0, 0, 0, "newArmy", "", false, 0, 0, false, 3, 0, "");
    Card card4("Ancient Woods", 1, 0, 1, 0, "buildCity", "newArmy", true, 0, 1, false, 0, 0, "");
    Card card5("Cursed Banshee", 0, 6, 0, 0, "moveArmy", "", false, 0, 0, false, 2, 0, "");
    Card card6("Cursed Gargoyles", 0, 5, 0, 0, "moveArmy", "", false, 0, 0, true, 0, 0, "");
    Card card7("Cursed King", 3, 4, 0, 0, "newArmy", "moveArmy", false, 0, 0, false, 1, 0, "");
    Card card8("Cursed Mausoleum", 0, 0, 1, 0, "buildCity", "", false, 1, 0, false, 0, 0, "");
    Card card9("Cursed Tower", 0, 0, 1, 0, "buildCity", "", false, 0, 0, false, 0, 0, "1VPperFlying");
    Card card10("Dire Dragon", 3, 0, 0, 1, "newArmy", "destroyArmy", true, 0, 0, true, 0, 0, "");
    Card card11("Dire Eye", 4, 0, 0, 0, "newArmy", "", false, 0, 0, true, 0, 0, "");
    Card card12("Dire Giant", 3, 0, 0, 1, "newArmy", "destroyArmy", true, 0, 0, false, 0, 0, "immuneToAttack");
    Card card13("Dire Goblin", 0, 5, 0, 0, "moveArmy", "", false, 0, 0, false, 1, 0, "");
    Card card14("Dire Ogre", 0, 2, 0, 0, "moveArmy", "", false, 0, 0, false, 0, 0, "1VPper3Coins");
    Card card15("Forest Elf", 3, 2, 0, 0, "newArmy", "moveArmy", false, 0, 1, false, 0, 0, "");
    Card card16("Forest Gnome", 0, 2, 0, 0, "moveArmy", "", false, 0, 0, false, 3, 0, "");
    Card card17("Forest Pixie", 0, 4, 0, 0, "moveArmy", "", false, 0, 1, false, 0, 0, "");
    Card card18("Forest Tree Town", 0, 0, 1, 0, "buildCity", "", false, 1, 0, false, 0, 0, "");
    Card card19("Graveyard", 2, 0, 0, 0, "newArmy", "", false, 0, 0, false, 0, 0, "1VPperCursedCard");
    Card card20("Lake", 2, 3, 0, 0, "newArmy", "moveArmy", false, 0, 0, false, 0, 0, "1VPperForestCard");
    Card card21("Night Hydra", 0, 5, 0, 1, "moveArmy", "destroyArmy", true, 0, 1, false, 0, 0, "");
    Card card22("Night Village", 0, 0, 1, 0, "buildCity", "", false, 0, 1, false, 0, 0, "");
    Card card23("Night Wizard", 3, 0, 0, 1, "newArmy", "destroyArmy", true, 0, 0, false, 0, 0, "1VPperNightCard");
    Card card24("Noble Hills", 3, 0, 0, 0, "newArmy", "", false, 0, 0, false, 0, 0, "3NobleCards=4VP");
    Card card25("Noble Knight", 4, 0, 0, 1, "newArmy", "destroyArmy", true, 1, 0, false, 0, 0, "");
    Card card26("Noble Unicorn", 1, 4, 0, 0, "moveArmy", "newArmy", true, 1, 0, false, 0, 0, "");
    Card card27("Stronghold", 0, 0, 1, 0, "buildCity", "", false, 0, 0, false, 0, 0, "1VPperDireCard");
    addCard(card1);
    addCard(card2);
    addCard(card3);
    addCard(card4);
    addCard(card5);
    addCard(card6);
    addCard(card7);
    addCard(card8);
    addCard(card9);
    addCard(card10);
    addCard(card11);
    addCard(card12);
    addCard(card13);
    addCard(card14);
    addCard(card15);
    addCard(card16);
    addCard(card17);
    addCard(card18);
    addCard(card19);
    addCard(card20);
    addCard(card21);
    addCard(card22);
    addCard(card23);
    addCard(card24);
    addCard(card25);
    addCard(card26);
    addCard(card27);

    //For more than 2 players
    if (numPlayer >= 3) {
        Card card28("Arcane Manticore", 4, 0, 0, 1, "newArmy", "destroyArmy", true, 1, 0, false, 0, 0, "");
        Card card29("Arcane Sphinx", 3, 4, 0, 0, "newArmy", "moveArmy", false, 0, 0, true, 0, 0, "");
        Card card30("Arcane Temple", 0, 3, 0, 0, "moveArmy", "", false, 0, 0, false, 0, 0, "1VPperArcaneCard");
        Card card31("Mountain Dwarf", 2, 0, 0, 1, "newArmy", "destroyArmy", true, 0, 0, false, 0, 0, "3VPfor2MountainCards");
        Card card32("Mountain Treasury", 0, 3, 0, 0, "moveArmy", "", false, 0, 0, false, 1, 2, "");
        addCard(card28);
        addCard(card29);
        addCard(card30);
        addCard(card31);
        addCard(card32);
    }

    if (numPlayer == 4) {
        Card card33("Castle", 3, 0, 1, 0, "newArmy", "buildCity", false, 0, 0, false, 1, 0, "");
        Card card34("Castle 2", 0, 3, 1, 0, "moveArmy", "buildCity", true, 0, 0, false, 1, 0, "");
        addCard(card33);
        addCard(card34);
    }

    //Shuffle the cards
    shuffle();
}

//Add cards into the deck
void Deck::addCard(Card newCard) {
    deck.push_back(newCard);
}

//Changing the index position of the cards in the deck using random number
void Deck::shuffle() {

    //http://www.cplusplus.com/reference/algorithm/random_shuffle/
    srand(unsigned(std::time(0)));
    random_shuffle(deck.begin(), deck.end());
    //random_shuffle(deck.begin(), deck.end(), int(time(0)));
}

//Debug function to reveals all cards in deck
void Deck::reveal() {
    cout << "!! This is a debug utility to reveals all cards in deck, cards will be drawn from the back !!" << endl;
    cout << "Current deck size: " << deck.size() << endl;
    for (unsigned i = 0; i < deck.size(); i++) {
        cout << (i + 1) << ". ";
        deck[i].print();
    }
    cout << "\n";
}

//Draw card from deck
Card Deck::draw() {

    if (deck.size() > 0) {
        Card tempCard = deck.back();
        cout << "The card drawn from deck is: " << deck.back().getName() << endl;
        deck.pop_back();
        return tempCard;
    }
    else { //If the deck is empty, the card being returned will be named "EMPTY"
        Card tempEmpty("EMPTY", 0, 0, 0, 0, "newArmy", "", false, 0, 0, false, 0, 0, "");
        return tempEmpty;
    }

}

//Getter
int Deck::getSize() {
    return deck.size();
}


//Hand is hardcoded to draw 6 cards from deck upon initialization
Hand::Hand(Deck& mainDeck) {

    addCard(mainDeck.draw());
    addCard(mainDeck.draw());
    addCard(mainDeck.draw());
    addCard(mainDeck.draw());
    addCard(mainDeck.draw());
    addCard(mainDeck.draw());
}

//Add new cards into the hand
void Hand::addCard(Card newCard) {
    hand.push_back(newCard);
}

//Print out all cards in Hand associated with their current cost for exchange
void Hand::showHand() {
    cout << "\n---Cards currently in Hand--- \n";

    for (unsigned i = 0; i < hand.size(); i++) {
        cout << "(Cost " << costCalc(i) << " coins) " << (i + 1) << ". ";
        hand[i].print();
    }
}

//Utility function for calculating cost of exchange dynamically besed on their current index position
int Hand::costCalc(int index) {
    if (index == 0) {
        return 0;
    }
    else if (index == 1 or index == 2) {
        return 1;
    }
    else if (index == 3 or index == 4) {
        return 2;
    }
    else {
        return 3;
    }

}

//Exchange function to allow player to buy cards from hand using coins
//showHand function included for demonstration
Card Hand::exchange(Deck& mainDeck) {
    int cardInput; //Position from user input
    int cardChoice; //Index position from hand vector
    Card cardChosen;

    if (hand.size() > 0) {
        showHand();
        cout << "Choose which card you'd like to exchange (1-6): " << endl;
        cin >> cardInput;

        if (cardInput > 0 && cardInput < (hand.size() + 1)) {
            cardChoice = cardInput - 1;
        }
        else {
            cout << "!invalid selection! Default to first free card. \n"; //Exception handler
            cardChoice = 0;
        }

        cardChosen = hand[cardChoice];

        cout << "The card you've selected to exchange is " << cardChosen.getName() << endl;

        //Remove the card chosen from Hand and move all cards after it to the left by 1 position
        for (int i = cardChoice; i < (hand.size() - 1); i++) {
            hand[i] = hand[i + 1];
        }
        //Remove the last now supposed to be emptry slot
        hand.pop_back();

        //Draw new card to place into the rightmost position
        Card cardAdded = mainDeck.draw();

        //Handle when the deck is empty
        if (cardAdded.getName() == "EMPTY") {
            cout << "No more new cards from deck" << endl;
        }
        else {
            addCard(cardAdded);
        }

        cout << "Here is the cards in Hand after the exchange" << endl;
        showHand();

        return cardChosen;
    }

    //Return card named "EMPTRY" when hand is empty
    else {
        Card tempEmpty("EMPTY", 0, 0, 0, 0, "newArmy", "", false, 0, 0, false, 0, 0, "");
        return tempEmpty;
    }


}

//Getter
int Hand::getSize() {
    return hand.size();
}


>>>>>>> Stashed changes
