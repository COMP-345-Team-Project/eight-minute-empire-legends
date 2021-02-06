#include "Map.h"
#include <string>

using namespace std;

// Territory function/constructor definitions

Territory::Territory(string name, string owner, int armies) 
	: name(name), owner(owner), armies(armies) { }

Territory::Territory(string name, string owner)
	: name(name), owner(owner), armies(0) { }

void Territory::setName(string name) {
	this->name = name;
}

void Territory::setOwner(string owner) {
	this->owner = owner;
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

int Territory::getArmies() {
	return this->armies;
}

string Territory::toString() {
	return "Name: " + this->name + "\nOwner: " + this->owner + "\nArmies: " + to_string(this->armies);
}
