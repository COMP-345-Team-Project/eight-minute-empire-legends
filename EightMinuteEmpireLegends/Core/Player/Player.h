#pragma once
#include "../pch.h"

#include "../Cards/Cards.h"
#include "../Map/Map.h"
#include "../Bidding/BiddingFacility.h"

class Player
{
public:
	Player(std::string name, BiddingFacility& biddingFacility);
	Player(const Player& player);
	~Player();

	int getCoins();
	int getAvailableArmies();
	int getAvailableCities();
	vector<Card> getCards();
	std::string getPlayerName();

	void PayCoin(int coins);
	void PlaceNewArmies(Map* map, Vertex* v, int numOfArmies); //We need to map to check for the starting region
	//To make things simple, we move armies 1 region at a time, and we ask the player the details for each move
	//We need to check if the edge is water/land in this method
	void MoveArmies(Map* map, Vertex* from, Vertex* to, int numOfArmies, int& remainingMoves);
	void BuildCity(Vertex* v, int numOfArmies);
	void DestroyArmy(Vertex* v, int numOfArmies);
	void InitResources(int coin, int armies, int cities);
	

private:
	std::string playerName;
	int coin;
	int availableArmies;
	int availableCities;
	vector<Vertex> deployedVertices;
	Hand hand;
	BiddingFacility biddingFacility;
};

class PlayerActionException : public std::exception
{
	private:
		std::string errorMessage;
	public:
		PlayerActionException(const std::string& msg);
		const char* what() const throw();
};
