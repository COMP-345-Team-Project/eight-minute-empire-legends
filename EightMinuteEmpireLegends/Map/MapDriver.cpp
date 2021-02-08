#include "MapDriver.h"
#include "Map.h"
#include <iostream>
#include <vector>

int main() {

	// Playing around with iterator object. Ignore this.

	/*
	vector<int> v1{};
	vector<int>::iterator it;
	
	v1.push_back(10);
	v1.push_back(9);
	v1.push_back(4);
	
	std::cout << v1.front() << ' ';
	std::cout << v1.at(1) << ' ';
	std::cout << v1.back() << std::endl;

	it = v1.begin();
	v1.erase(it++);

	string str = "V" + to_string(abs((int)&v1));
	std::cout << (int)&v1 << std::endl;
	std::cout << str;

	Vertex v1 = Vertex(t1, "V" + to_string((int)&v1));
	Vertex v2 = Vertex(t2, "V" + to_string((int)&v2));
	Vertex v3 = Vertex(t1, "V" + to_string((int)&v3));
	Vertex v4 = Vertex(t2, "V" + to_string((int)&v4));
	*/
	
	Territory t1 = Territory("Quebec", "Jacque", 3);	
	Territory t2 = Territory("Ontario", "Tom");

	Vertex v1 = Vertex(t1, "u");
	Vertex v2 = Vertex(t2, "v");
	Vertex v3 = Vertex(t1, "w");
	Vertex v4 = Vertex(t2, "z");

	Edge e1 = Edge(v1, v2, "e");
	Edge e2 = Edge(v1, v3, "g");
	Edge e3 = Edge(v2, v3, "f");
	Edge e4 = Edge(v3, v4, "h");

	Continent c1 = Continent("C1");	

	std::cout << v1.getId() << std::endl << std::endl;
	std::cout << v2.getId() << std::endl << std::endl;
	std::cout << v1.getTerritory().toString()  << std::endl << std::endl;
	
	std::cout << e1.getId() << std::endl << std::endl;
	std::cout << e1.getEndpoints()[0].getId() << ' ' << e1.getEndpoints()[1].getId() << std::endl << std::endl;	

	std::cout << c1.insertVertex(v1) << c1.insertVertex(v2) << c1.insertVertex(v3) << c1.insertVertex(v4) << std::endl << std::endl;
	std::cout << c1.insertEdge(e1) << c1.insertEdge(e2) << c1.insertEdge(e3) << c1.insertEdge(e4) << std::endl << std::endl;
	std::cout << c1.numVertices() << std::endl << std::endl;
	std::cout << vertices_toString(c1.vertices()) << std::endl << std::endl;
	std::cout << c1.numEdges() << std::endl << std::endl;
	std::cout << edges_toString(c1.edges()) << std::endl << std::endl;
	std::cout << c1.getEdge(v1, v2)->getId() << std::endl << std::endl;
	std::cout << c1.getEdge(v1, v4) << std::endl << std::endl;
	std::cout << c1.endVertices(&e1)[0].getId() << ' ' << c1.endVertices(&e1)[1].getId() << std::endl << std::endl;
	std::cout << c1.opposite(v1, &e1)->getId() << std::endl << std::endl;

	return 0;
}
