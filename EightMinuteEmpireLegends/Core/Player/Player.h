#pragma once
#include "../pch.h"

#include "../Cards/Cards.h"
#include "../Map/Map.h"
#include "../Bidding/BiddingFacility.h"

class Player
{
public:
	//Constructors
	Player(std::string name, BiddingFacility* biddingFacility);
	Player(const Player& player);
	~Player();

	//Getters
	int getCoins() const;
	int getAvailableArmies() const;
	int getAvailableCities() const;
	vector<Card> getCards();
	std::string getPlayerName() const;

	//Player actions
	bool HasArmyDeployedInVertex(Vertex* v); 
	void PayCoin(int coins);
	void PlaceNewArmies(Map* map, Vertex* v, int numOfArmies); //We need to map to check for the starting region
	//To make things simple, we move armies 1 region at a time, and we ask the player the details for each move
	//We need to check if the edge is water/land in this method
	void MoveArmies(Map* map, Vertex* from, Vertex* to, int numOfArmies, int& remainingMoves);
	void BuildCity(Vertex* v, int numOfArmies);
	void DestroyArmy(Vertex* v, int numOfArmies);
	void InitResources(int coin, int armies, int cities);
	int ComputeScore(Map* map);

	//Operators overloading
	Player& operator =(const Player& p);
	friend std::ostream& operator <<(std::ostream& os, const Player* p);
	

private:
	//Private data members
	std::string playerName;
	int coin;
	int availableArmies;
	int availableCities;
	vector<Vertex*> deployedVertices;
	CardSpace hand;
	BiddingFacility* biddingFacility;

	//Private methods
	void AddDeployedVertex(Vertex* v);
	void RemoveDeployedVertex(Vertex* v);
	int ComputeTerritoryScore();
	int ComputeRegionalScore(Map* map);
	bool OwnsContinent(std::map<string, int>& continentScores);
	int CountCardsBasedOnType(string cardType);
	int ComputeAbilityScore();
};

class PlayerActionException : public std::exception
{
	private:
		std::string errorMessage;
	public:
		PlayerActionException(const std::string& msg);
		const char* what() const throw();
};
