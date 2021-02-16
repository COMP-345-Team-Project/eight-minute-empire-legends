#include "MapDriver.h"
#include "Map.h"
#include <iostream>
#include <vector>

int main() {

	/*
	Vertex v1 = Vertex(t1, "V" + to_string((int)&v1));
	Vertex v2 = Vertex(t2, "V" + to_string((int)&v2));
	Vertex v3 = Vertex(t1, "V" + to_string((int)&v3));
	Vertex v4 = Vertex(t2, "V" + to_string((int)&v4));
	*/
	
	struct Continent c1, c2, c3, c4;
	c1.name = "NA";
	c2.name = "SA";
	c3.name = "Africa";
	c4.name = "Europe";

	enum subgraph { Apple, Orange, Pear };

	std::vector<Continent*> c{ &c1, &c2, &c3, &c4 };
	Map m1 = Map("Earth", c);

	Territory t1 = Territory("Quebec", c1.name);
	Territory t2 = Territory(t1);		
	Territory t3 = Territory("BC", c3.name);

	Vertex v1 = Vertex(&t1, "u");
	Vertex v2 = Vertex(&t2, "v");
	Vertex v3 = Vertex(&t1, "w");
	Vertex v4 = Vertex(&t2, "z");
	Vertex v5 = Vertex(&t3, "a");

	t2.setName("Ontario");
	t2.setOwner("Thomas");
	t2.setArmies(25);
	t1.setOwner("Jacque");
	t1.setArmies(50);	

	Edge e1 = Edge(&v1, &v2, "e");
	Edge e2 = Edge(&v1, &v3, "g");
	Edge e3 = Edge(&v2, &v3, "f");
	Edge e4 = Edge(&v3, &v4, "h");			

	std::cout << "ID of vertex 1 is " << v1.getId() << std::endl;
	std::cout << "ID of vertex 2 is " << v2.getId() << std::endl;
	std::cout << "Territory of vertex 1: \n" << v1.getTerritory()->toString() << std::endl;
	std::cout << "Territory of vertex 2: \n" << v2.getTerritory()->toString() << std::endl;
	
	std::cout << "ID of edge {u, v} is " << e1.getId() << std::endl;
	std::cout << "Endpoints of edge e are " << e1.getEndpoints()[0]->getId() << ' ' << e1.getEndpoints()[1]->getId() << std::endl;			

	std::cout << "Inserting vertices to graph: " << m1.insertVertex(&v1) << m1.insertVertex(&v2) << m1.insertVertex(&v3) << m1.insertVertex(&v4) << m1.insertVertex(&v5) << std::endl;
	std::cout << "Inserting edges to graph: " << m1.insertEdge(&e1) << m1.insertEdge(&e2) << m1.insertEdge(&e3) << m1.insertEdge(&e4) << std::endl;
	std::cout << "Number of vertices in graph is " << m1.numVertices() << std::endl;
	std::cout << "List of vertices in graph: " << vertices_toString(m1.vertices()) << std::endl;
	std::cout << "Number of edges in graph is " << m1.numEdges() << std::endl;
	std::cout << "List of edges in graph: " << edges_toString(m1.edges()) << std::endl;
	std::cout << "Number of continents in graph: " << m1.numContinents() << std::endl;
	std::cout << "List of subgraphs in graphs: " << continents_toString(m1.continents()) << std::endl;
	std::cout << "ID of edge connecting vertices {w, z} is " << m1.getEdge(&v3, &v4)->getId() << std::endl;	
	std::cout << "Edge e connects vertices " << m1.endVertices(&e1)[0]->getId() << " and " << m1.endVertices(&e1)[1]->getId() << std::endl;
	std::cout << "Vertex u is connected by edge e to vertex " << m1.opposite(&v1, &e1)->getId() << std::endl;
	std::cout << "Degree of vertex u is " << m1.degree(&v1) << " and degree of vertex z is " << m1.degree(&v4) << std::endl;
	
	Edge e5 = Edge(&v1, &v4, "i");
	std::cout << "New edge 'i' is created connecting vertices u and z: " << std:: endl;

	std::cout << "Inserting edge i to graph: " << m1.insertEdge(&e5) << std::endl;
	std::cout << "Now degree of vertex u is " << m1.degree(&v1) << " and degree of vertex z is " << m1.degree(&v4) << std::endl;
	std::cout << "Updated list of edges in graph: " << edges_toString(m1.edges()) << std::endl;
	std::cout << "Incident edges to vertex u are " << edges_toString(m1.edges(&v1)) << std::endl;
	
	std::cout << "Removing edge i from graph: " << m1.removeEdge("i") << std::endl;
	std::cout << "Now degree of vertex u is " << m1.degree(&v1) << " and degree of vertex z is " << m1.degree(&v4) << std::endl;
	std::cout << "Incident edges to vertex u are now " << edges_toString(m1.edges(&v1)) << std::endl;

	std::cout << "Removing vertex w: " << m1.removeVertex("w") << std::endl;

	std::cout << "Removing Vertex w from the graph, remaining edges will be " << edges_toString(m1.edges()) << std::endl;	
	std::cout << "Updated list of vertices - " << vertices_toString(m1.vertices()) << std::endl;
	
	std::cout << "All vertices in continent NA - " << vertices_toString(m1.vertices(&c1)) << std::endl;
	m1.removeVertex(v1.getId());
	std::cout << "All vertices in continent NA - " << vertices_toString(m1.vertices(&c1)) << std::endl;
	

	return 0;
}
