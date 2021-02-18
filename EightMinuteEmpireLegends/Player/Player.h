#pragma once
#include <vector>
#include "../Map/Map.h"
#include "../Cards/Cards.h"
#include "../BiddingFacility/BiddingFacility.h"

class Player
{
public:
	Player();
	~Player();
	Player(Map map, Hand hand, BiddingFacility biddingFacility, std::string name);
	int PayCoin();
	void PlaceNewArmies(vector<Vertex*> vv);
	bool MoveArmies(Vertex* v1, Vertex* v2);
	bool MoveOverLand(Vertex* v1, Vertex* v2);
	bool BuildCity(Vertex* v);
	bool DestroyArmy(Vertex* v);
private:
	Map map;
	Hand hand;
	BiddingFacility biddingFacility;
	int coin;
	std::string name;
	vector<Vertex*> cities;
};

