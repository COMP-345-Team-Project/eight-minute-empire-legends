#pragma once

#include <iostream>
#include <map>
#include <string>

class NameSorter
{
private:
	std::string * lastNameLeader;

public:
	NameSorter();
	void addName(std::string newName);
	std::string getLeader();
};

