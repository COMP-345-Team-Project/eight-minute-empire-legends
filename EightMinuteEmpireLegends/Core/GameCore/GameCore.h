#pragma once
#include "../pch.h"
#include "../GameObservers/GameObservers.h"
#include "../Cards/Cards.h"
#include "../Player/Player.h"
#include "../Bidding/BidTieBreakerByLastName.h"
#include "../MapLoader/MapLoader.h"
#include "../MapLoader/MapLoaderException.h"
#include "ConfigFileException.h"
#include "GameBuilderException.h"

const int _dCoins = 36;
const int _dArmies = 18;
const int _dCities = 3;

// ../Tests/GameStartTests/Resources
const std::string _mapDir = "../Tests/GameStartTests/Resources";
// ../../config/EightMinuteEmpireLengendsPrefs.ini
const std::string _configPath = "../../config/EightMinuteEmpireLengendsPrefs.ini";

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
    friend std::ostream& operator <<(std::ostream& os, const Resources* r);
    int getAssignedCities();
};

class Game : public Observable {
private:
    Resources* resources;
    Map* map;
    Deck* deck;
    std::vector<Player*> players;
    Player* neutralPlayer = nullptr; // Initialized if 2 player game

    void _placeArmies(); //2 players game are a bit different, check rules
    void _bid(); //Gather user inputs, then call the BiddingFacility to actually do the bidding
    bool _isEndGame();
    int _getVertexIndexFromUserInput(vector<Vertex*> vertices, std::string prompt);
    int _getArmiesForOperation(int limit);
    int _getPlayerIndexFromUserInput(std::string prompt);
    
    
    void _promptPlayerToPerformAction(Card* card, std::string actionDisplay, int actionOrder, Player* player);
    

public:
    Game();
    Game(Resources* resources, Map* map, Deck* deck, vector<Player*> players);
    ~Game();

    // Getters
    Resources* getResources();
    Map* getMap();
    Deck* getDeck();
    std::vector<Player*> getPlayers();
    void displayTerritories(std::vector<Vertex*> vertices);
    void displayTerritories(std::vector<Vertex*> vertices, bool numbered);
    friend std::ostream& operator <<(std::ostream& os, const Game* g);

    //Set up phase
    void runSetupPhase();

    //Main game loop, part 3, 5
    void runRoundsUntilEndGame();

    //End game, announce winners, and cleanup
    void endGame();
    //End game
    void endGame(Map* map, vector<Player*> players);

    //Helper functions
    void PlaceArmies(Player* player, int numOfArmies);
    void MoveArmies(Player* player, int deployLimit);
    void BuildCity(Player* player);
    void DestroyArmies(Player* currPlayer, int detroyLimit);
    Vertex* FindVertexById(Map* map, string id);

    static void _listActions(Card* card);
    static bool _confirm();

    void _performAction(Card* card, Player* player, int actionNumber);

    void _assignResources(); //Call assignResources() from resource, need to be public for testing

    //Observable abstract class implementation
    void notify();
};