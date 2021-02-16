#pragma once
#include <string>
#include <vector>

// Class forward declarations

class Map;
class Continent;
class Edges;
class Vertex;
class Territory;

// Territory class declaration

class Territory
{
private:
	std::string name;
	std::string owner;
	Continent* const c;
	int armies;
public:
	Territory(std::string name, Continent* c);
	Territory(Territory* t);
	Territory();

	void setName(std::string name);
	void setOwner(std::string owner);
	void setArmies(int armies);
	std::string getName();
	std::string getOwner();
	Continent* getContinent();
	int getArmies();
	std::string toString();
};

// Vertex class declaration

class Vertex
{
private:
	std::string id;
	Territory* const t;
public:
	Vertex(Territory* t, std::string id);
	Vertex();

	std::string getId();
	Territory getTerritory();
	bool compare(Vertex* v);
};

// Edge class declaration

class Edge
{
private:
	std::string id;
	Vertex* v1;
	Vertex* v2;
public:
	Edge(Vertex* v1, Vertex* v2, std::string id);
	Edge();

	std::string getId();
	std::vector<Vertex*> getEndpoints();
	bool crossContinent();
};

// Continent class declaration

class Continent
{
private:
	std::string name;
	std::vector<Vertex*> v_vertices;
	std::vector<Edge*> v_edges;
	void removeEdgeCatalyst(std::string id);
public:
	Continent(std::string name);
	Continent();

	void setName(std::string name);
	std::string getName();
	int numVertices();
	std::vector<Vertex*> vertices();
	int numEdges();
	std::vector<Edge*> edges();
	Edge* getEdge(Vertex* v1, Vertex* v2);
	std::vector<Vertex*> endVertices(Edge* e);
	Vertex* opposite(Vertex* v, Edge* e);
	int degree(Vertex* v);
	std::vector<Edge*> edges(Vertex* v);
	bool insertVertex(Vertex* v);
	bool insertEdge(Edge* e);
	bool removeVertex(std::string id);
	bool removeEdge(std::string id);
};

// Map class declaration

class Map
{
private:
	std::vector<Continent*> continents;
public:
	Map();

	bool addContinent(Continent* c);
	bool removeContinent(Continent* c);
	bool validate();
};
