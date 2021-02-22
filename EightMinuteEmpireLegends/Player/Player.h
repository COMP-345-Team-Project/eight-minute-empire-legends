#pragma once
#include "../Cards/Cards.h"
#include "../Map/Map.h"
#include "../BiddingFacility/BiddingFacility.h"

class Player
{
public:
	Player(std::string name, Deck deck, BidTieBreaker& bidTieBreaker);
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
