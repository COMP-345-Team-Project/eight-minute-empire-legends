#pragma once
#include "../pch.h"
#include "PlayerType.h"

struct PlayerContext {
	std::string firstName;
	std::string lastName;
	PlayerType strategy;
};