#include "../pch.h"
#include "PlayerStrategies.h"
//#include "Player.h"

Strategy::Strategy() {}

HumanStrategy::HumanStrategy() {}

GreedyStrategy::GreedyStrategy() {}

ModerateStrategy::ModerateStrategy() {}

void Strategy::buyCard() {
	std::cout << "BaseClass buyCard()" << std::endl; //For Debug
}
void Strategy::performAction() {
	std::cout << "BaseClass performAction()" << std::endl; //For Debug
}

void HumanStrategy::buyCard() {
	std::cout << "Human buyCard()" << std::endl;
}

void HumanStrategy::performAction() {
	std::cout << "Human performAction()" << std::endl;
}

void GreedyStrategy::buyCard() {
	std::cout << "Greedy buyCard()" << std::endl;
}

void GreedyStrategy::performAction() {
	std::cout << "Greedy performAction()" << std::endl;
}

void ModerateStrategy::buyCard() {
	std::cout << "Moderate buyCard()" << std::endl;
}

void ModerateStrategy::performAction() {
	std::cout << "Moderate buyCard()" << std::endl;
}



