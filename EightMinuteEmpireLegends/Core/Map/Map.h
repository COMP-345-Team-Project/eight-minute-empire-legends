#pragma once
#include "../pch.h"

// Class forward declarations

class Map;
struct Continent;
class Edges;
class Vertex;
class Territory;

// Territory class declaration

class Territory
{
private:
	std::string name;
	std::string owner;	
	int armies;		
	std::string const c;
public:
	Territory(std::string name, std::string c);
	Territory(const Territory* t);
	Territory();		

	void setName(std::string name);
	void setOwner(std::string owner);
	void setArmies(int armies);
	std::string getName();
	std::string getOwner();	
	int getArmies();
	std::string getContinent();
	Territory& operator =(const Territory& t);
	friend std::ostream& operator <<(std::ostream& os, const Territory* t);
};

// Vertex class declaration

class Vertex
{
private:
	std::string id;
	Territory* const t;
public:
	Vertex(Territory* t, std::string id);
	Vertex(const Vertex* v);
	Vertex();
	~Vertex();

	std::string getId();
	Territory* getTerritory();
	bool compare(Vertex* v);
	Vertex& operator =(const Vertex& v);
	friend std::ostream& operator <<(std::ostream& os, const Vertex* v);
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
	Edge(const Edge* e);
	Edge();		

	std::string getId();
	std::vector<Vertex*> getEndpoints();	
	Edge& operator =(const Edge& e);
	friend std::ostream& operator <<(std::ostream& os, const Edge* e);
};

// Continent struct declaration

struct Continent
{
	std::string name;
	friend std::ostream& operator <<(std::ostream& os, const Continent* c);
};

// Map class declaration

class Map
{
private:
	std::string name;
	std::vector<Vertex*> v_vertices;
	std::vector<Edge*> v_edges;
	std::vector<Continent*> v_continents;	
	Vertex* startingRegion;
	void cascadeRemoveEdge(std::string id);
	void dfs(Vertex* v, std::vector<Vertex*>* visited);
	bool exists(std::string c);
public:
	Map(std::string name, std::vector<Continent*> c);
	Map(const Map* m);
	Map();
	~Map();
	
	std::string getName();
	void setStartingRegion(Vertex* v);
	Vertex* getStartingRegion();
	int numVertices();
	std::vector<Vertex*> vertices();		
	int numEdges();
	std::vector<Edge*> edges();	
	int numContinents();
	std::vector<Continent*> continents();
	Edge* getEdge(Vertex* v1, Vertex* v2);
	std::vector<Vertex*> endVertices(Edge* e);
	Vertex* opposite(Vertex* v, Edge* e);
	int degree(Vertex* v);
	std::vector<Edge*> edges(Vertex* v);
	std::vector<Vertex*> vertices(Continent* c);
	std::vector<Vertex*> adjacentVertices(Vertex* v);
	bool insertVertex(Vertex* v);
	bool insertEdge(Edge* e);
	bool removeVertex(std::string id);
	bool removeEdge(std::string id);
	bool validate();	
	Map& operator =(const Map& m);
	friend std::ostream& operator <<(std::ostream& os, const Map* m);
};