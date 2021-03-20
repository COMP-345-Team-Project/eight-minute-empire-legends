#pragma once
#include "../pch.h"

#include "../Cards/Cards.h"
#include "../Map/Map.h"
#include "../Bidding/BiddingFacility.h"

class Player
{
public:
	Player(std::string name, Deck deck, BiddingFacility& biddingFacility);
	~Player();
	void payCoin();
	void PlaceNewArmies();
	void MoveArmies();
	void MoveOverLand();
	void BuildCity();
	void DestroyArmy();

private:
	std::string playerName;
	int coin;
	Map map;
	Hand hand;
	BiddingFacility biddingFacility;
};
