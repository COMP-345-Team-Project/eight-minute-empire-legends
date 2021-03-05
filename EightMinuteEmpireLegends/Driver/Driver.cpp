#pragma once
#include "../Core/pch.h"

#include "AssignmentOneDriver.h"

int main(int argc, char** argv) {
	std::cout << "(1) Running the Map Driver..." << std::endl;
	runMapDriver();
	std::cout << "\n(2) Running the Map Loader Driver..." << std::endl;
	runMapLoaderDriver();
	std::cout << "\n(3) Running the Player Driver..." << std::endl;
	runPlayerDriver();
	std::cout << "\n(4) Running the Card Driver..." << std::endl;
	runCardsDriver();
	std::cout << "\n(5) Running the Bidding Facility Driver (the driver uses assertions so there will be no output)..." << std::endl;
	runBiddingFacilityDriver();
}
