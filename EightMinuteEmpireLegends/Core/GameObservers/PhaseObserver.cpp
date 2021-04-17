#include "../pch.h"
#include "PhaseObserver.h"

PhaseObserver::PhaseObserver() {};

PhaseObserver::PhaseObserver(Player* p) : _player(p) {
	_player->attach(this);
};

PhaseObserver::~PhaseObserver() {
	_player->detach(this);
};

void PhaseObserver::update() {	
	displayMessage();
};

void PhaseObserver::displayMessage() {
	std::cout << "\n---------" << _player->getPlayerName() << " : " << _player->getLastActionMessage() << "---------\n" << std::endl;
};
