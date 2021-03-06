#pragma once

#include "Driver.h"

// This is the entrypoint to our Game, Test Suite, and Assignment Drivers

int main(int argc, char** argv) 
{
	// TODO: Parse command line arguments and execute corresponding driver with params.

	Driver driver;
	driver.RunAssignmentOneDriver();

	return 0;
}
