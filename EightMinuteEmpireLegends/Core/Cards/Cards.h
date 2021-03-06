#pragma once

#include "../pch.h"
//#include <algorithm>    // std::random_shuffle
//#include <ctime>        // std::time
//#include <cstdlib>      // std::rand, std::srand

using namespace std;

class Card {

public:
    Card(string nameValue, int newArmyValue, int moveArmyValue, int buildCityValue, int destroyArmyValue,
        string firstActionValue, string secondActionValue, bool andActionValue, int extraMoveValue,
        int extraArmyValue, bool flyingValue, int elixerValue, int extraCoinValue, string specialAbilityValue);
    Card();

    //Print out card's attributes
    void print();

    //Utility function for printing car's action string
    void printHelper(string str);

    //Getter
    string getName();
    int getNewArmy();
    int getMoveArmy();
    int getBuildCity();
    int getDestroyArmy();
    string getFirstAction();
    string getSecondAction();
    bool getAndAction();
    int getExtraMove();
    int getExtraArmy();
    bool getFlying();
    int getElixer();
    int getExtraCoin();
    string getSpecialAbility();

private:
    string name;

    //Action
    int newArmy;
    int moveArmy;
    int buildCity;
    int destroyArmy;

    //2 Action handler
    string firstAction;
    string secondAction;
    bool andAction;

    //Ability
    int extraMove;
    int extraArmy;
    bool flying;
    int elixer;
    int extraCoin;

    //Special Ability
    string specialAbility;

};


class Deck {

public:

    Deck();

    Deck(int numPlayer);

    //Add cards into the deck
    void addCard(Card newCard);

    //Changing the index position of the cards in the deck using random number
    void shuffle();

    //Debug function to reveals all cards in deck
    void reveal();
    //Draw card from deck
    Card draw();

    //Getter
    int getSize();

private:
    vector<Card> deck;

};


class Hand {

public:

    //Hand is hardcoded to draw 6 cards from deck upon initialization
    Hand(Deck& mainDeck);

    //Add new cards into the hand
    void addCard(Card newCard);

    //Print out all cards in Hand associated with their current cost for exchange
    void showHand();

    //Utility function for calculating cost of exchange dynamically besed on their current index position
    int costCalc(int index);

    //Exchange function to allow player to buy cards from hand using coins
    //showHand function included for demonstration
    Card exchange(Deck& mainDeck, bool demo);

    //Getter
    int getSize();

private:
    vector<Card> hand;
};