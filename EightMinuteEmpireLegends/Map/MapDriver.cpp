#include "MapDriver.h"
#include "Map.h"
#include <iostream>

int main() {

	// Valid map example

	Continent c1, c2, c3, c4;
	c1.name = "Europe";
	c2.name = "Asia";
	c3.name = "Africa";
	c4.name = "Oceania";	

	Territory* t1 = new Territory("France", c1.name);
	Territory* t2 = new Territory("Germany", c1.name);
	Territory* t3 = new Territory("Egypt", c3.name);
	Territory* t4 = new Territory("Uganda", c3.name);
	Territory* t5 = new Territory("China", c2.name);
	Territory* t6 = new Territory("New Zealand", c4.name);
	std::vector<Territory*> v_t{ t1, t2, t3, t4, t5, t6 };

	Vertex* v1 = new Vertex(t1, "u");
	Vertex* v2 = new Vertex(t2, "v");
	Vertex* v3 = new Vertex(t3, "w");
	Vertex* v4 = new Vertex(t4, "x");
	Vertex* v5 = new Vertex(t5, "y");
	Vertex* v6 = new Vertex(t6, "z");
	std::vector<Vertex*> v_v{ v1, v2, v3, v4, v5, v6 };

	Edge* e1 = new Edge(v1, v2, "a");
	Edge* e2 = new Edge(v1, v3, "b");
	Edge* e3 = new Edge(v3, v4, "c");
	Edge* e4 = new Edge(v2, v4, "d");
	Edge* e5 = new Edge(v1, v4, "e");
	Edge* e6 = new Edge(v2, v3, "f");
	Edge* e7 = new Edge(v2, v5, "g");
	Edge* e8 = new Edge(v4, v5, "h");
	Edge* e9 = new Edge(v5, v6, "i");
	std::vector<Edge*> v_e{ e1, e2, e3, e4, e5, e6, e7, e8, e9 };

	Map* m1 = new Map("Earth", { &c1, &c2, &c3, &c4 });

	m1->insertVertex(v1);
	m1->insertVertex(v2);
	m1->insertVertex(v3);
	m1->insertVertex(v4);
	m1->insertVertex(v5);
	m1->insertVertex(v6);

	m1->insertEdge(e1);
	m1->insertEdge(e2);
	m1->insertEdge(e3);
	m1->insertEdge(e4);
	m1->insertEdge(e5);
	m1->insertEdge(e6);
	m1->insertEdge(e7);
	m1->insertEdge(e8);
	m1->insertEdge(e9);

	std::cout << "Validating Map 1 - " << (m1->validate() ? "Valid" : "invalid") << std::endl;	

	// Invalid map example		

	Map* m2 = new Map("Earth", { &c1, &c2, &c3, &c4 });

	m2->insertVertex(v1);
	m2->insertVertex(v2);
	m2->insertVertex(v3);
	m2->insertVertex(v4);
	m2->insertVertex(v5);
	m2->insertVertex(v6);

	// Notice that we are not inserting edge e7 and e8 in our graph, which means vectors v5 and v6 will be disconnected
	m2->insertEdge(e1);
	m2->insertEdge(e2);
	m2->insertEdge(e3);
	m2->insertEdge(e4);
	m2->insertEdge(e5);
	m2->insertEdge(e6);
	m2->insertEdge(e9);

	std::cout << "Validating Map 2 - " << (m2->validate() ? "Valid" : "Invalid") << std::endl << std::endl;

	// Graph information on Map 1
	std::cout << "Map 1 " << vertices_toString(m1->vertices()) << std::endl;
	std::cout << "Map 1 " << edges_toString(m1->edges()) << std::endl;
	std::cout << "Map 1 " << continents_toString(m1->continents()) << std::endl;
	std::cout << "Map 1 " << territories_toString(m1->vertices()) << std::endl;
	std::cout << "Map 1 " << continents_toString(m1) << std::endl << std::endl;

	// Graph information on Map 2
	std::cout << "Map 2 " << vertices_toString(m2->vertices()) << std::endl;
	std::cout << "Map 2 " << edges_toString(m2->edges()) << std::endl;
	std::cout << "Map 2 " << continents_toString(m2->continents()) << std::endl;
	std::cout << "Map 2 " << territories_toString(m2->vertices()) << std::endl;
	std::cout << "Map 2 " << continents_toString(m2) << std::endl;	

	// Deleting variables in heap
	for (Territory* t : v_t) {
		delete t;
	}
	for (Vertex* v : v_v) {
		delete v;
	}
	for (Edge* e : v_e) {
		delete e;
	}
	delete m1;
	delete m2;

	while (1) { }
	
	return 0;
}
