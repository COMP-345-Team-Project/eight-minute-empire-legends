#pragma once
#include "../pch.h"
#include <iostream>
#include "../GameObservers/GameObservers.h"
#include "../Player/player.h"

class PhaseObserver : public Observer
{
private:
	Player* _player;
	std::string context;
public:
	PhaseObserver();
	PhaseObserver(Player* p);
	~PhaseObserver();
	void Update(std::string context);
	void Display();
};

