#include "../pch.h"
#include "PhaseObserver.h"

PhaseObserver::PhaseObserver() {};

PhaseObserver::PhaseObserver(Player* p) : _player(p) {
	_player->Attach(this);
};

PhaseObserver::~PhaseObserver() {
	_player->Detach(this);
};

void PhaseObserver::Update(std::string context) {
	this->context = context;
	Display();
};

void PhaseObserver::Display() {
	std::cout << _player->getPlayerName() << " : " << context << std::endl;
};
