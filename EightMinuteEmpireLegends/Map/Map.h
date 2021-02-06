#pragma once
#include <string>

using namespace std;

class Map
{

};

class Territory
{
private:
	string name;
	string owner;
	string continent;	
	int armies;
public:	

	Territory(string name, string owner, string continent, int armies);
	Territory(string name, string owner, string continent);

	void setName(string name);
	void setOwner(string owner);
	void setContinent(string continent);
	void setArmies(int armies);

	string getName();
	string getOwner();
	string getContinent();
	int getArmies();
	string toString();
};

