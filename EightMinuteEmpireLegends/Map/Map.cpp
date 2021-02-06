#include "Map.h"
#include <string>

using namespace std;

Territory::Territory(string name, string owner, string continent, int armies) 
	: name(name), owner(owner), continent(continent), armies(armies) { }

Territory::Territory(string name, string owner, string continent)
	: name(name), owner(owner), continent(continent), armies(0) { }

void Territory::setName(string name) {
	this->name = name;
}

void Territory::setOwner(string owner) {
	this->owner = owner;
}

void Territory::setContinent(string continent) {
	this->continent = continent;
}

void Territory::setArmies(int armies) {
	this->armies = armies;
}

string Territory::getName() {
	return this->name;
}

string Territory::getOwner() {
	return this->owner;
}

string Territory::getContinent() {
	return this->continent;
}

int Territory::getArmies() {
	return this->armies;
}

string Territory::toString() {
	return "Name: " + this->name + "\nOwner: " + this->owner + "\nContinent: " + this->continent + "\nArmies: " + to_string(this->armies);
}
