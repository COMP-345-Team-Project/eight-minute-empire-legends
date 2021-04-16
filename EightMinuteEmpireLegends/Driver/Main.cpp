#pragma once

#include "Driver.h"

int main(int argc, char** argv) 
{
	// TODO: Parse command line arguments and execute corresponding driver with params.

	Driver driver;
	//driver.RunAssignmentOneDriver();
	//driver.RunAssignmentTwoDriver();
	driver.RunStrategyDriver();

	return 0;
}
