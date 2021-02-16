#include "NameSorter.h"

NameSorter::NameSorter()
{
	this->lastNameLeader = nullptr;
}

void NameSorter::addName(std::string newName)
{
	if (newName < *this->lastNameLeader) {
		*this->lastNameLeader = newName;
	}
}

std::string NameSorter::getLeader()
{
	return *this->lastNameLeader;
}
