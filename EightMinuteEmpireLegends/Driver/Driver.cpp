#include "Driver.h"
#include "AssignmentOneDriver.h"

int Driver::RunAssignmentOneDriver()
{
	AssignmentOneDriver ass1Driver;
	std::cout << "(1) Running the Map Driver..." << std::endl;
	ass1Driver.RunMapDriver();
	std::cout << "\n(2) Running the Map Loader Driver..." << std::endl;
	ass1Driver.RunMapLoaderDriver();
	std::cout << "\n(3) Running the Player Driver..." << std::endl;
	ass1Driver.RunPlayerDriver();
	std::cout << "\n(4) Running the Card Driver..." << std::endl;
	ass1Driver.RunCardsDriver();
	std::cout << "\n(5) Running the Bidding Facility Driver (the driver uses assertions so there will be no output)..." << std::endl;
	ass1Driver.RunBiddingFacilityDriver();
	return 0;
}
