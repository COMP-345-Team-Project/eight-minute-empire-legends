#pragma once
#include <string>
#include <vector>

// Territory class declaration

class Territory
{
private:
	std::string name;
	std::string owner;
	int armies;
public:

	Territory(std::string name, std::string owner, int armies);
	Territory(std::string name, std::string owner);

	void setName(std::string name);
	void setOwner(std::string owner);
	void setArmies(int armies);

	std::string getName();
	std::string getOwner();
	int getArmies();
	std::string toString();
};

// Vertex class declaration

class Vertex
{
private:
	std::string id;
	Territory t;
public:
	Vertex(Territory t, std::string id);

	std::string getId();
	Territory getTerritory();
	bool compare(Vertex v);
};

// Edge class declaration

class Edge
{
private:
	std::string id;
	Vertex v1;
	Vertex v2;
public:
	Edge(Vertex v1, Vertex v2, std::string id);

	std::string getId();
	std::vector<Vertex> getEndpoints();
};

// Continent class declaration

class Continent
{
private:
	std::string name;
	std::vector<Vertex> v_vertices;
	std::vector<Edge> v_edges;
public:
	Continent(std::string name);

	void setName(std::string name);
	std::string getName();

	int numVertices();
	std::vector<Vertex> vertices();
	int numEdges();
	std::vector<Edge> edges();
	Edge* getEdge(Vertex v1, Vertex v2);
	std::vector<Vertex> endVertices(Edge *e);
	Vertex* opposite(Vertex v, Edge *e);
	int degree(Vertex v);
	std::vector<Edge> edges(Vertex v);
	bool insertVertex(Vertex v);
	bool insertEdge(Edge e);
	bool removeVertex(std::string id);
	bool removeEdge(std::string id);
};

// Map class declaration

class Map
{
private:
	std::vector<Continent> continents;
public:
	Map();

	bool addContinent(Continent c);
	bool removeContinent(Continent c);
	bool validate();
};
