#pragma once
#include "../pch.h"
#include <iostream>
#include "GameObservers.h"
#include "../Player/player.h"

class PhaseObserver : public Observer
{
private:
	Player* _player;

	void displayMessage();
public:
	PhaseObserver();
	PhaseObserver(Player* p);
	~PhaseObserver();
	void update();
};
