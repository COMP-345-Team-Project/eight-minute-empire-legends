#include "MapDriver.h"
#include "Map.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {

	// Playing around with iterator object. Ignore this.

	vector<int> v1{};
	vector<int>::iterator it;
	
	v1.push_back(10);
	v1.push_back(9);
	v1.push_back(4);
	
	cout << v1.front() << ' ';
	cout << v1.at(1) << ' ';
	cout << v1.back() << endl;

	it = v1.begin();
	v1.erase(it++);

	string str = "V" + to_string(abs((int)&v1));
	cout << (int)&v1 << endl;
	cout << str;
	return 0;
}

