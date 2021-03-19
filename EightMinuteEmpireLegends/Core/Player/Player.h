#pragma once
#include "../pch.h"

#include "../Cards/Cards.h"
#include "../Map/Map.h"
#include "../Bidding/BiddingFacility.h"

class Player
{
public:
	Player(std::string name, Deck deck, BidTieBreaker& bidTieBreaker);
	Player(const Player& player);
	~Player();
	void PayCoin(int coins);
	void PlaceNewArmies(Vertex v, int numOfArmies);
	//To make things simple, we move armies 1 region at a time, and we ask the player the details for each move
	//We need to check if the edge is water/land in this method
	void MoveArmies(Vertex from, Vertex to, int numOfArmies);
	void BuildCity(Vertex v, int numOfArmies);
	void DestroyArmy(Vertex v, int numOfArmies);
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
