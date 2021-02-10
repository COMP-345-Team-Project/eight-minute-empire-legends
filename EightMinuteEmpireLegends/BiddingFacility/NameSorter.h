#pragma once

#include <iostream>
#include <map>
#include <string>

class NameSorter
{
private:
	//std::map<std::string, std::string> guidNameMap;
	std::string lastNameLeader;

public:
	NameSorter();
	void addName(std::string newName);
	std::string getLeader();
};

