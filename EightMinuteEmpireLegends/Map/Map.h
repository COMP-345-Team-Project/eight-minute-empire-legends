#pragma once
#include <string>
#include <vector>

using namespace std;

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

// Vertex class declaration

class Vertex
{
private:
	string id;
	Territory t;
public:
	Vertex(Territory t, string id);

	string getId();
	Territory getTerritory();
	bool compare(Vertex v);
};

// Edge class declaration

class Edge
{
private:
	string id;
	Vertex v1;
	Vertex v2;
public:
	Edge(Vertex v1, Vertex v2, string id);

	string getId();
	vector<Vertex> getEndpoints();
};

// Continent class declaration

class Continent
{
private:
	string name;
	vector<Vertex> v_vertices;	
	vector<Edge> v_edges;	
public:
	Continent(string name);

	void setName(string name);
	string getName();

	int numVertices();
	vector<Vertex> vertices();
	int numEdges();
	vector<Edge> edges();
	Edge* getEdge(Vertex v1, Vertex v2);
	vector<Vertex> endVertices(Edge *e);
	Vertex* opposite(Vertex v, Edge *e);
	int degree(Vertex v);
	vector<Edge> edges(Vertex v);
	bool insertVertex(Vertex v);
	bool insertEdge(Edge e);
	bool removeVertex(string id);
	bool removeEdge(string id);
};

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