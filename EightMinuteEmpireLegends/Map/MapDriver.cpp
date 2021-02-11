#include "MapDriver.h"
#include "Map.h"
#include <iostream>
#include <vector>

int main() {

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
	
	Territory t1 = Territory("Quebec");	
	Territory t2 = Territory(t1);	

	Vertex v1 = Vertex(&t1, "u");
	Vertex v2 = Vertex(&t2, "v");
	Vertex v3 = Vertex(&t1, "w");
	Vertex v4 = Vertex(&t2, "z");

	t1.setOwner("Jacque");
	t1.setArmies(50);
	t2.setName("Ontario");
	t2.setOwner("Thomas");
	t2.setArmies(25);

	Edge e1 = Edge(&v1, &v2, "e");
	Edge e2 = Edge(&v1, &v3, "g");
	Edge e3 = Edge(&v2, &v3, "f");
	Edge e4 = Edge(&v3, &v4, "h");		

	Continent c1 = Continent("C1");	

	std::cout << "ID of vertex 1 is " << v1.getId() << std::endl << std::endl;
	std::cout << "ID of vertex 2 is " << v2.getId() << std::endl << std::endl;
	std::cout << "Territory of vertex 1: \n" << v1.getTerritory().toString()  << std::endl << std::endl;
	std::cout << "Territory of vertex 2: \n" << v2.getTerritory().toString()  << std::endl << std::endl;
	
	std::cout << "ID of edge {u, v} is " << e1.getId() << std::endl << std::endl;
	std::cout << "Endpoints of edge e are " << e1.getEndpoints()[0]->getId() << ' ' << e1.getEndpoints()[1]->getId() << std::endl << std::endl;	

	std::cout << "Inserting vertices to graph: " << c1.insertVertex(&v1) << c1.insertVertex(&v2) << c1.insertVertex(&v3) << c1.insertVertex(&v4) << std::endl << std::endl;
	std::cout << "Inserting edges to graph: " << c1.insertEdge(&e1) << c1.insertEdge(&e2) << c1.insertEdge(&e3) << c1.insertEdge(&e4) << std::endl << std::endl;
	std::cout << "Number of vertices in graph is " << c1.numVertices() << std::endl << std::endl;
	std::cout << "List of vertices in graph: " << vertices_toString(c1.vertices()) << std::endl << std::endl;
	std::cout << "Number of edges in graph is " << c1.numEdges() << std::endl << std::endl;
	std::cout << "List of edges in graph: " << edges_toString(c1.edges()) << std::endl << std::endl;
	std::cout << "ID of edge connecting vertices {w, z} is " << c1.getEdge(&v3, &v4)->getId() << std::endl << std::endl;	
	std::cout << "Edge e connects vertices " << c1.endVertices(&e1)[0]->getId() << " and " << c1.endVertices(&e1)[1]->getId() << std::endl << std::endl;
	std::cout << "Vertex u is connected by edge e to vertex " << c1.opposite(&v1, &e1)->getId() << std::endl << std::endl;
	std::cout << "Degree of vertex u is " << c1.degree(&v1) << " and degree of vertex z is " << c1.degree(&v4) << std::endl << std::endl;

	Edge e5 = Edge(&v1, &v4, "i");
	std::cout << "New edge 'i' is created connecting vertices u and z: " << std:: endl << std::endl;

	std::cout << "Inserting edge i to graph: " << c1.insertEdge(&e5) << std::endl << std::endl;
	std::cout << "Now degree of vertex u is " << c1.degree(&v1) << " and degree of vertex z is " << c1.degree(&v4) << std::endl << std::endl;
	std::cout << "Updated list of edges in graph: " << edges_toString(c1.edges()) << std::endl << std::endl;
	std::cout << "Incident edges to vertex u are " << edges_toString(c1.edges(&v1)) << std::endl << std::endl;
	
	std::cout << "Removing edge i from graph: " << c1.removeEdge("i") << std::endl << std::endl;
	std::cout << "Now degree of vertex u is " << c1.degree(&v1) << " and degree of vertex z is " << c1.degree(&v4) << std::endl << std::endl;
	std::cout << "Incident edges to vertex u are now " << edges_toString(c1.edges(&v1)) << std::endl << std::endl;

	c1.removeVertex("w");
	std::cout <<"Removing Vertex w from the graph, remaining edges will be " << edges_toString(c1.edges()) << std::endl << std::endl;	

	return 0;
}
