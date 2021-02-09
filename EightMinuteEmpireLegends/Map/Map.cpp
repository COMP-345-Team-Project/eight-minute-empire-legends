#include "Map.h"
#include <string>
#include <vector>
#include <list>

// Continent function/constructor definitions

Continent::Continent(std::string name)
	: name(name) { }

int Continent::numVertices() {
	return this->v_vertices.size();
}

std::vector<Vertex*> Continent::vertices() {
	return this->v_vertices;
}

int Continent::numEdges() {
	return this->v_edges.size();
}

std::vector<Edge*> Continent::edges() {
	return this->v_edges;
}

Edge* Continent::getEdge(Vertex *v1, Vertex *v2) {
	for (Edge* e : this->v_edges) {
		if (e->getEndpoints()[0]->compare(v1) && e->getEndpoints()[1]->compare(v2)
			|| e->getEndpoints()[0]->compare(v2) && e->getEndpoints()[1]->compare(v1)) {
			return e;
		}
	}	
	return nullptr;
}

std::vector<Vertex*> Continent::endVertices(Edge *e) {
	return e != nullptr ? e->getEndpoints() : std::vector<Vertex*>();
}

Vertex* Continent::opposite(Vertex *v, Edge *e) {
	if (e != nullptr) {
		if (e->getEndpoints()[0]->compare(v)) {
			return e->getEndpoints()[1];
		}
		else if (e->getEndpoints()[1]->compare(v)) {
			return e->getEndpoints()[0];
		}
		else {
			return nullptr;
		}
	}
	return nullptr;
}

int Continent::degree(Vertex *v) {
	int degree = 0;
	for (Edge* e : this->v_edges) {
		if (e->getEndpoints()[0]->compare(v) || e->getEndpoints()[1]->compare(v)) {
			degree++;
		}
	}
	return degree;
}

std::vector<Edge*> Continent::edges(Vertex *v) {
	std::vector<Edge*> incidents {};
	for (Edge* e : this->v_edges) {
		if (e->getEndpoints()[0]->compare(v) || e->getEndpoints()[1]->compare(v)) {
			incidents.push_back(e);			
		}
	}
	return incidents;
}

bool Continent::insertVertex(Vertex *v) {	
	for (Vertex* ver : this->v_vertices) {
		if (ver->getId() == v->getId()) {
			return false;
		}
	}
	this->v_vertices.push_back(v);
	return true;
}

bool Continent::insertEdge(Edge *e) {
	if (getEdge(e->getEndpoints()[0], e->getEndpoints()[1]) == nullptr) {
		this->v_edges.push_back(e);
		return true;
	}
	return false;
}

bool Continent::removeVertex(std::string id) {
	std::vector<Vertex*>::iterator it = this->v_vertices.begin();
	for (Vertex* v : this->v_vertices) {
		if (v->getId() == id) {
			this->v_vertices.erase(it);
			// This is kinda dumb ngl
			removeEdgeCatalyst(v->getId());
			return true;
		}
		it++;
	}
	return false;
}

void Continent::removeEdgeCatalyst(std::string id) {
	std::list<Edge*>  l{ std::begin(this->v_edges), std::end(this->v_edges) };	

	l.remove_if([id](Edge* const e) { return (e->getEndpoints()[0]->getId() == id || e->getEndpoints()[1]->getId() == id); });	

	//this->v_edges = v{ std::begin(l.begin()), std::end(l.end()) };
}

bool Continent::removeEdge(std::string id) {
	std::vector<Edge*>::iterator it = this->v_edges.begin();
	for (Edge* e : this->v_edges) {
		if (e->getId() == id) {
			this->v_edges.erase(it);
			return true;
		}
		it++;
	}
	return false;
}

// Vertex function/constructor definitions

Vertex::Vertex(Territory *t, std::string id)
	: t(t), id(id) { }

std::string Vertex::getId() {
	return this->id;
}

Territory Vertex::getTerritory() {
	return this->t;
}

bool Vertex::compare(Vertex *v) {
	return this->id == v->getId();
}

// Edge function/constructor definitions

Edge::Edge(Vertex *v1, Vertex *v2, std::string id)
	: v1(v1), v2(v2), id(id) { }

std::string Edge::getId() {
	return this->id;
}

std::vector<Vertex*> Edge::getEndpoints() {
	return { this->v1, this->v2 };
}

// Territory function/constructor definitions

Territory::Territory(std::string name)
	: name(name), owner(""), armies(0) { }

Territory::Territory(Territory *t)
	: name(t->getName()), owner(t->getOwner()), armies(t->getArmies()) { }

void Territory::setName(std::string name) {
	this->name = name;
}

void Territory::setOwner(std::string owner) {
	this->owner = owner;
}

void Territory::setArmies(int armies) {
	this->armies += armies;
}

std::string Territory::getName() {
	return this->name;
}

std::string Territory::getOwner() {
	return this->owner;
}

int Territory::getArmies() {
	return this->armies;
}

std::string Territory::toString() {
	return "Name: " + this->name + "\nOwner: " + this->owner + "\nArmies: " + std::to_string(this->armies);
}
