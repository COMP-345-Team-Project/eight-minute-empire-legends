#pragma once

#include "../../Core/Map/Map.h"

#include "MapTestUtils.h"
#include "MapTests.h"


int MapTests::Test_ValidatingValidMapConstruction_ReturnsTrue()
{
	// Valid map example	

	Continent* c1 = new Continent();
	c1->name = "Europe";
	Continent* c2 = new Continent();
	c2->name = "Asia";
	Continent* c3 = new Continent();
	c3->name = "Africa";
	Continent* c4 = new Continent();
	c4->name = "Oceania";

	Territory* t1 = new Territory("France", c1->name);
	Territory* t2 = new Territory("Germany", c1->name);
	Territory* t3 = new Territory("Egypt", c3->name);
	Territory* t4 = new Territory("Uganda", c3->name);
	Territory* t5 = new Territory("China", c2->name);
	Territory* t6 = new Territory("New Zealand", c4->name);

	Vertex* v1 = new Vertex(t1, "u");
	Vertex* v2 = new Vertex(t2, "v");
	Vertex* v3 = new Vertex(t3, "w");
	Vertex* v4 = new Vertex(t4, "x");
	Vertex* v5 = new Vertex(t5, "y");
	Vertex* v6 = new Vertex(t6, "z");

	Edge* e1 = new Edge(v1, v2, "a");
	Edge* e2 = new Edge(v1, v3, "b");
	Edge* e3 = new Edge(v3, v4, "c");
	Edge* e4 = new Edge(v2, v4, "d");
	Edge* e5 = new Edge(v1, v4, "e");
	Edge* e6 = new Edge(v2, v3, "f");
	Edge* e7 = new Edge(v2, v5, "g");
	Edge* e8 = new Edge(v4, v5, "h");
	Edge* e9 = new Edge(v5, v6, "i");

	Map* m1 = new Map("Earth", { c1, c2, c3, c4 });

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

	std::cout << "Validating Map 1 - " << (m1->validate() ? "Valid" : "Invalid") << std::endl;
	// Graph information on Map 1
	std::cout << "Map 1 " << vertices_toString(m1->vertices()) << std::endl;
	std::cout << "Map 1 " << edges_toString(m1->edges()) << std::endl;
	std::cout << "Map 1 " << continents_toString(m1->continents()) << std::endl;
	std::cout << "Map 1 " << territories_toString(m1->vertices()) << std::endl;
	std::cout << "Map 1 " << continents_toString(m1) << std::endl << std::endl;

	int isValid = m1->validate() ? 0 : 1;
	delete m1;
	return isValid;
}

int MapTests::Test_ValidatingInvalidMapConstruction_ReturnsFalse()
{
	// Invalid map example	

	Continent* cc1 = new Continent();
	cc1->name = "Europe";
	Continent* cc2 = new Continent();
	cc2->name = "Asia";
	Continent* cc3 = new Continent();
	cc3->name = "Africa";
	Continent* cc4 = new Continent();
	cc4->name = "Oceania";

	Territory* tt1 = new Territory("France", cc1->name);
	Territory* tt2 = new Territory("Germany", cc1->name);
	Territory* tt3 = new Territory("Egypt", cc3->name);
	Territory* tt4 = new Territory("Uganda", cc3->name);
	Territory* tt5 = new Territory("China", cc2->name);
	Territory* tt6 = new Territory("New Zealand", cc4->name);

	Vertex* vv1 = new Vertex(tt1, "u");
	Vertex* vv2 = new Vertex(tt2, "v");
	Vertex* vv3 = new Vertex(tt3, "w");
	Vertex* vv4 = new Vertex(tt4, "x");
	Vertex* vv5 = new Vertex(tt5, "y");
	Vertex* vv6 = new Vertex(tt6, "z");


	Edge* ee1 = new Edge(vv1, vv2, "a");
	Edge* ee2 = new Edge(vv1, vv3, "b");
	Edge* ee3 = new Edge(vv3, vv4, "c");
	Edge* ee4 = new Edge(vv2, vv4, "d");
	Edge* ee5 = new Edge(vv1, vv4, "e");
	Edge* ee6 = new Edge(vv2, vv3, "f");
	Edge* ee9 = new Edge(vv5, vv6, "i");

	Map* m2 = new Map("Earth", { cc1, cc2, cc3, cc4 });

	m2->insertVertex(vv1);
	m2->insertVertex(vv2);
	m2->insertVertex(vv3);
	m2->insertVertex(vv4);
	m2->insertVertex(vv5);
	m2->insertVertex(vv6);

	// Notice that we are not inserting edge e7 and e8 in our graph, which means vectors v5 and v6 will be disconnected
	m2->insertEdge(ee1);
	m2->insertEdge(ee2);
	m2->insertEdge(ee3);
	m2->insertEdge(ee4);
	m2->insertEdge(ee5);
	m2->insertEdge(ee6);
	m2->insertEdge(ee9);

	std::cout << "Validating Map 2 - " << (m2->validate() ? "Valid" : "Invalid") << std::endl << std::endl;

	// Graph information on Map 2
	std::cout << "Map 2 " << vertices_toString(m2->vertices()) << std::endl;
	std::cout << "Map 2 " << edges_toString(m2->edges()) << std::endl;
	std::cout << "Map 2 " << continents_toString(m2->continents()) << std::endl;
	std::cout << "Map 2 " << territories_toString(m2->vertices()) << std::endl;
	std::cout << "Map 2 " << continents_toString(m2) << std::endl;

	int isValid = m2->validate() ? 0 : 1;
	delete m2;
	return isValid;
}
