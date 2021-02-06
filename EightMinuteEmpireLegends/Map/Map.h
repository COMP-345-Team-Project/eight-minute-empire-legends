#pragma once
#include <string>
#include <vector>

using namespace std;

// Map class declaration

class Map
{
private:	
	vector<Continent> continents;
public:
	Map();

	bool addContinent(Continent c);
	bool removeContinent(Continent c);
	bool validate();
};

// Continent class declaration

class Continent
{
private:
	string name;
	vector<Vertex> vertices;
	vector<Edge> edges;
public:
	Continent(string name);

	void setName(string name);
	string getName();

	int numVertices();
	int vertices();
	int numEdges();
	int edges();
	Edge getEdge(Vertex v1, Vertex v2);
	vector<Vertex> endVertices(Edge e);
	Vertex opposite(Vertex v, Edge e);
	int degree(Vertex v);
	vector<Edge> edges(Vertex v);
	void insertVertex(Territory t);
	bool insertEdge(Vertex v1, Vertex v2, int index);
	bool removeVertex(int index);
	bool removeEdge(int index);	
};

// Vertex class declaration

class Vertex
{
private:
	int index;	
	Territory terr;
public:
	Vertex(Territory terr, int index);

	int getIndex();
	Territory getTerritory();		
};

// Edge class declaration

class Edge 
{
private:
	int index;
	Vertex v1;
	Vertex v2;
public:
	Edge(Vertex v1, Vertex v2, int index);	
	
	int getIndex();	
};

// Territory class declaration

class Territory
{
private:
	string name;
	string owner;	
	int armies;
public:	

	Territory(string name, string owner, int armies);
	Territory(string name, string owner);

	void setName(string name);
	void setOwner(string owner);	
	void setArmies(int armies);

	string getName();
	string getOwner();	
	int getArmies();
	string toString();
};
