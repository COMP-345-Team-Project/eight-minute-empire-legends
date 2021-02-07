#include "Map.h"
#include <string>
#include <vector>

using namespace std;

// Continent function/constructor definitions

Continent::Continent(string name) 
	: name(name) { }

int Continent::numVertices() {
	return this->v_vertices.size();
}

vector<Vertex> Continent::vertices() {
	return this->v_vertices;
}

int Continent::numEdges() {
	return this->v_edges.size();
}

vector<Edge> Continent::edges() {
	return this->v_edges;
}

Edge* Continent::getEdge(Vertex v1, Vertex v2) {
	for (Edge e : this->v_edges) {
		if (e.getEndpoints()[0].compare(v1) && e.getEndpoints()[1].compare(v2)
			|| e.getEndpoints()[0].compare(v2) && e.getEndpoints()[1].compare(v1)) {
			return &e;
		}
	}	
}

vector<Vertex> Continent::endVertices(Edge *e) {
	return e != NULL ? e->getEndpoints() : vector<Vertex>();
}

Vertex Continent::opposite(Vertex v, Edge *e) {
	if (e != NULL) {
		if (e->getEndpoints()[0].compare(v)) {
			return e->getEndpoints()[1];
		}
		else {
			return e->getEndpoints()[0];
		}
	}	
}

int Continent::degree(Vertex v) {
	int degree = 0;
	for (Edge e : this->v_edges) {
		if (e.getEndpoints()[0].compare(v) || e.getEndpoints()[1].compare(v)) {
			degree++;
		}
	}
	return degree;
}

vector<Edge> Continent::edges(Vertex v) {
	vector<Edge> incidents {};	
	for (Edge e : this->v_edges) {
		if (e.getEndpoints()[0].compare(v) || e.getEndpoints()[1].compare(v)) {
			incidents.push_back(e);			
		}
	}
	return incidents;
}

void Continent::insertVertex(Territory t, string id) {	
	this->v_vertices.push_back(Vertex(t, id));
}

bool Continent::insertEdge(Vertex v1, Vertex v2, string id) {
	if (getEdge(v1, v2) == NULL) {
		this->v_edges.push_back(Edge(v1, v2, id));
		return true;
	}
	return false;
}

bool Continent::removeVertex(string id) {
	vector<Vertex>::iterator it = this->v_vertices.begin();
	for (Vertex v : this->v_vertices) {
		if (v.getId() == id) {
			this->v_vertices.erase(it);
			return true;
		}
		it++;
	}
	return false;
}

bool Continent::removeEdge(string id) {
	vector<Edge>::iterator it = this->v_edges.begin();
	for (Edge e : this->v_edges) {
		if (e.getId() == id) {
			this->v_edges.erase(it);
			return true;
		}
		it++;
	}
	return false;
}

// Vertex function/constructor definitions

Vertex::Vertex(Territory t, string id)
	: t(t), id(id) { }

string Vertex::getId() {
	return this->id;
}

Territory Vertex::getTerritory() {
	return this->t;
}

bool Vertex::compare(Vertex v) {
	return this->id == v.getId();
}

// Edge function/constructor definitions

Edge::Edge(Vertex v1, Vertex v2, string id)
	: v1(v1), v2(v2), id(id) { }

string Edge::getId() {
	return this->id;
}

vector<Vertex> Edge::getEndpoints() {
	return { this->v1, this->v2 };
}

// Territory function/constructor definitions

Territory::Territory(string name, string owner, int armies) 
	: name(name), owner(owner), armies(armies) { }

Territory::Territory(string name, string owner)
	: name(name), owner(owner), armies(0) { }

void Territory::setName(string name) {
	this->name = name;
}

void Territory::setOwner(string owner) {
	this->owner = owner;
}

void Territory::setArmies(int armies) {
	this->armies = armies;
}

string Territory::getName() {
	return this->name;
}

string Territory::getOwner() {
	return this->owner;
}

int Territory::getArmies() {
	return this->armies;
}

string Territory::toString() {
	return "Name: " + this->name + "\nOwner: " + this->owner + "\nArmies: " + to_string(this->armies);
}
