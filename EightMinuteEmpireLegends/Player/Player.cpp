#include "Player.h"

Player::Player() : coin(14), name("") {} //we need to discuss the default constructors tomorrow (what class should be responsible for what task, and what information is present at what level of the hierarchy)

Player::Player(Map map, Hand hand, BiddingFacility biddingFacility, std::string name) :
	map(map), hand(hand), biddingFacility(biddingFacility), coin(14), name(name) {}

int Player::PayCoin(int n) {
	coin -= n;
	return coin;
}

//the following methods are assuming 1 player / territory, per current implementation of territory
bool Player::PlaceNewArmies(vector<Vertex*> vv) {
	//check if all the given vertex are owned by the player or are unoccupied
	for (Vertex* v : vv) {
		std::string owner = v->getTerritory->getOwner();
		if (owner.compare(name) != 0 && owner.compare("") != 0) {
			return false;
		}
	}
	for (Vertex* v : vv) {
		Territory* t = v->getTerritory();
		int army = t->getArmies();
		t->setArmies(++army);
		t->setOwner(name);
	}
	return true;
}

bool Player::DestroyArmy(Vertex* v) {
	//check if v has army to destroy 
	int army = v->getTerritory()->getArmies();
	if (--army < 0) {
		return false;
	}
	t->setArmies(army);
	if (army == 0) {
		t->setOwner("");
	}
	return true;
}

bool Player::MoveArmies(Vertex* v1, Vertex* v2) {
	//check v1 and v2 are linked by land
	std::string c1 = v1->getTerritory()->getContinent();
	std::string c2 = v2->getTerritory()->getContinent();
	if (c1.compare(c2) != 0) {
		return false;
	}
	return MoveOverLand(v1, v2);
}

bool Player::MoveOverLand(Vertex* v1, Vertex* v2) {
	//check v1 and v2 are adjacent in the map 
	bool v1AdjacentToV2 = false;
	for (Vertex* v : map.adjacentVertices(v1)) {
		if (v->compare(v2)) {
			v1AdjacentToV2 = true;
		}
	}
	if (!v1AdjacentToV2) {
		return false;
	}
	//check v1 has enough army to move 
	int army = v1->getTerritory()->getArmies();
	if (army < 1) {
		return false;
	}
	DestroyArmy(v1);
	vector<Vertex*> vv2;
	vv2.push_back(v2);
	PlaceNewArmies(vv2);
	return true;
}

bool Player::BuildCity(Vertex* v) {
	//check if an army exists in the territory/the player owns the territory, otherwise a city cannot be built
	std::string owner = v->getTerritory()->getOwner();
	if (owner.compare(name) != 0) {
		return false;
	}
	//check if city has already been built here by the player, if so it cannot be rebuilt
	bool cityExists = v->getTerritory()->getCity();
	if (cityExists) {
		return false;
	}
	v->getTerritory()->setCity(1);
	return true;
}

