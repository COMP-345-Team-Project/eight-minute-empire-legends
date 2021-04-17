#pragma once
#include "../pch.h"

#include "PlayerScore.h"
#include "../Cards/Cards.h"
#include "../Map/Map.h"
#include "../Bidding/BiddingFacility.h"
#include "PlayerStrategies.h"
#include "../GameObservers/GameObservers.h"

class Player : public Observable
{
public:
	//Constructors
	Player(std::string name, BiddingFacility* biddingFacility);
	Player(std::string name, BiddingFacility* biddingFacility, bool isNeutral);
	Player(const Player& player);
	~Player();

	//Getters
	bool isNeutralPlayer();
	int getCoins() const;
	int getAvailableArmies() const;
	int getAvailableCities() const;
	vector<Card*> getCards();
	void addCard(Card* card);
	std::string getPlayerName() const;
	void addElixirs(int elixir);
	int getElixirs();
	Strategy* getStrategy();
	std::string getLastActionMessage();

	//Player actions
	bool HasArmyDeployedInVertex(Vertex* v); 
	void BuyCard(Card* cardBought, int costs);
	void PayCoin(int coins);
	void PlaceNewArmies(Map* map, Vertex* v, int numOfArmies); //We need to map to check for the starting region
	//To make things simple, we move armies 1 region at a time, and we ask the player the details for each move
	//We need to check if the edge is water/land in this method
	void MoveArmies(Map* map, Vertex* from, Vertex* to, int numOfArmies, int& remainingMoves);
	void BuildCity(Vertex* v, int numOfCities);
	void DestroyArmy(Vertex* v, Player* opponent, int numOfArmies);
	void InitResources(int coin, int armies, int cities);
	int ComputeScore(Map* map, vector<Player*> players);
	void AddDeployedVertex(Vertex* v);
	int GetTerritoriesScore();
	int GetContinentsScore();
	int GetAbilitiesScore();
	int GetElixirScore();
	int GetTotalScore();
	vector<Vertex*> GetDeployedVertices();
	PlayerScore getPlayerScore();
	
	//Operators overloading
	Player& operator =(const Player& p);
	friend std::ostream& operator <<(std::ostream& os, const Player* p);

	//Strategy
	void setStrategy(string strategy);	

	// Observable override
	void notify();

private:
	//Private data members
	bool isNeutral;
	std::string playerName;
	int coin;
	int availableArmies;
	int availableCities;
	vector<Vertex*> deployedVertices;
	vector<Card*> cards;
	std::string lastActionMessage;
	
	BiddingFacility* biddingFacility;
	int elixir;

	//Strategy
	Strategy* strategy;

	//Private methods
	void RemoveDeployedVertex(Vertex* v);
	bool OwnsContinent(std::map<string, int>& continentScores);
	int CountCardsBasedOnType(string cardType);
	PlayerScore playerScore;
	int ComputeTerritoryScore();
	int ComputeRegionalScore(Map* map);
	int ComputeAbilityScore();
	int ComputeElixirScore(vector<Player*> players);
};

class PlayerActionException : public std::exception
{
	private:
		std::string errorMessage;
	public:
		PlayerActionException(const std::string& msg);
		const char* what() const throw();
};

class PlayerBuilder {
public:
	static void setPlayersType(vector<Player*> players);	
};