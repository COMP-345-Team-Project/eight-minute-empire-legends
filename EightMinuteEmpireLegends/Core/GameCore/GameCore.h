#pragma once
#include "../pch.h"
#include "../Cards/Cards.h"
#include "../Player/Player.h"
#include "../Bidding/BidTieBreakerByLastName.h"
#include "ConfigFileException.h"

const int _dCoins = 36;
const int _dArmies = 18;
const int _dCities = 3;

//This represent the pile of resources provided by the game board
class Resources {
private:
    int coins; //default is 36
    int armies; //default is 18
    int cities; //default is 3

public:
    Resources();
    Resources(int coins, int armies, int cities);

    //assign the initial resources to each player for the game setup
    void assignInitialResources(vector<Player*> players);
    //Resources& operator =(const Resources& r);
    //friend std::ostream& operator <<(std::ostream& os, const Resources* r);
};

class Game {
private:
    Resources* resources;
    Map* map;
    Deck* deck;
    vector<Player*> players;

    void _placeArmies(); //2 players game are a bit different, check rules
    void _assignResources(); //Call assignResources() from resource
    void _bid(); //Gather user inputs, then call the BiddingFacility to actually do the bidding
    bool _isEndGame();

public:
    Game(Resources& resources, Map& map, Deck& deck, vector<Player*> players);
    ~Game();

    //Set up phase
    void startUp();

    //Main game loop, part 3, 5
    void startGame();

    //End game
    void endGame();
};

//We use a GameBuilder to create a new game object instead of initializing the Game object directly
class GameBuilder {
public:
    static Game* build(int numPlayers, Map& map, std::string path = "");    
};

//We need to separate the concerns of the Hand class, which is fuzzy right now. We split Hand into CardSpace (the cards available for purchase, part of deck) and Hand (the cards owned by the player)
class CardSpace {
private:
    vector<Card*> available; //Store the 6 cards that are available for purchase

public:
    CardSpace(vector<Card*> available);

     //Add new cards into the hand
    void addCard(Hand& hand, Card* newCard);

    //Add the card of top of the deck to the card space
    void updateCardSpace();

    //Print out all cards in Hand associated with their current cost for exchange
    void showCardSpace();

    //Utility function for calculating cost of exchange dynamically besed on their current index position
    int costCalc(int index);
};

std::tuple<int, int, int> fetchConfigResources(std::string path);