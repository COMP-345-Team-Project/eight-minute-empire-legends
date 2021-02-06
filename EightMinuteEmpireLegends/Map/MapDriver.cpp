#include "MapDriver.h"
#include "Map.h"
#include <iostream>

using namespace std;

int main() {

	Territory t1 = Territory("Quebec", "Jacque", "NA", 3);
	Territory t2 = Territory("Ontario", "Jacque", "NA");

	cout << t1.toString() << endl;
	cout << t2.toString() << endl;

	return 0;
}

