#include "Map.h"

// Map function/constructor definitions

Map::Map(std::string name, std::vector<Continent*> c)
	: name(name), v_vertices({}), v_edges({}), v_continents(c), startingRegion(nullptr) { }

Map::Map()
	: name(""), v_vertices({}), v_edges({}), v_continents({}), startingRegion(nullptr) { }

std::string Map::getName() {
	return this->name;
}

void Map::setStartingRegion(Vertex* v) {
	this->startingRegion = v;
}

Vertex* Map::getStartingRegion() {
	return this->startingRegion;
}

int Map::numVertices() {
	return this->v_vertices.size();
}

std::vector<Vertex*> Map::vertices() {
	return this->v_vertices;
}

int Map::numEdges() {
	return this->v_edges.size();
}

std::vector<Edge*> Map::edges() {
	return this->v_edges;
}

int Map::numContinents() {
	return this->v_continents.size();
}

std::vector<Continent*> Map::continents() {
	return this->v_continents;
}

Edge* Map::getEdge(Vertex* v1, Vertex* v2) {
	for (Edge* e : this->v_edges) {
		if (e->getEndpoints()[0]->compare(v1) && e->getEndpoints()[1]->compare(v2)
			|| e->getEndpoints()[0]->compare(v2) && e->getEndpoints()[1]->compare(v1)) {
			return e;
		}
	}
	return nullptr;
}

std::vector<Vertex*> Map::endVertices(Edge* e) {
	return e != nullptr ? e->getEndpoints() : std::vector<Vertex*>();
}

// Dangling pointer warning. Should fix in the future.
Vertex* Map::opposite(Vertex* v, Edge* e) {
	if (e != nullptr) {
		if (e->getEndpoints()[0]->compare(v)) {
			return e->getEndpoints()[1];
		}
		else if (e->getEndpoints()[1]->compare(v)) {
			return e->getEndpoints()[0];
		}
	}
	return nullptr;
}

int Map::degree(Vertex* v) {
	int degree = 0;
	for (Edge* e : this->v_edges) {
		if (e->getEndpoints()[0]->compare(v) || e->getEndpoints()[1]->compare(v)) {
			degree++;
		}
	}
	return degree;
}

std::vector<Edge*> Map::edges(Vertex* v) {
	std::vector<Edge*> incidents{};
	for (Edge* e : this->v_edges) {
		if (e->getEndpoints()[0]->compare(v) || e->getEndpoints()[1]->compare(v)) {
			incidents.push_back(e);
		}
	}
	return incidents;
}

std::vector<Vertex*> Map::vertices(Continent* c) {
	std::vector<Vertex*> regions{};

	for (Vertex* v : this->v_vertices) {
		if (v->getTerritory()->getContinent() == c->name) {
			regions.push_back(v);
		}
	}
	return regions;
}

std::vector<Vertex*> Map::adjacentVertices(Vertex* v) {
	std::vector<Vertex*> av{};

	for (Edge* e : edges(v)) {
		av.push_back(opposite(v, e));
	}
	return av;
}

bool Map::insertVertex(Vertex* v) {
	if (exists(v->getTerritory()->getContinent())) {
		for (Vertex* ver : this->v_vertices) {
			if (ver->getId() == v->getId() || ver->getTerritory()->getName() == v->getTerritory()->getName()) {
				return false;
			}
		}
		this->v_vertices.push_back(v);
		return true;
	}
	return false;
}

bool Map::insertEdge(Edge* e) {
	if (getEdge(e->getEndpoints()[0], e->getEndpoints()[1]) == nullptr) {
		this->v_edges.push_back(e);
		return true;
	}
	return false;
}

bool Map::removeVertex(std::string id) {
	std::vector<Vertex*>::iterator it = this->v_vertices.begin();
	for (Vertex* v : this->v_vertices) {
		if (v->getId() == id) {
			this->v_vertices.erase(it);
			cascadeRemoveEdge(v->getId());
			return true;
		}
		it++;
	}
	return false;
}

// Removes all incident edges of a deleted vertex.
void Map::cascadeRemoveEdge(std::string id) {
	std::vector<Edge*>::iterator begin = this->v_edges.begin();
	std::vector<Edge*>::iterator end = this->v_edges.end();

	this->v_edges.erase(std::remove_if(begin, end, [id](Edge* const e) { return (e->getEndpoints()[0]->getId() == id || e->getEndpoints()[1]->getId() == id); }), end);
}

bool Map::removeEdge(std::string id) {
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

bool Map::exists(std::string c) {
	for (Continent* con : this->v_continents) {
		if (con->name == c) {
			return true;
		}
	}
	return false;
}

bool Map::validate() {
	std::vector<Vertex*> visited{};
	Vertex* first = this->v_vertices.at(0);
	dfs(first, &visited);
	return (visited.size() == this->v_vertices.size() && this->v_continents.size() > 1);
}

void Map::dfs(Vertex* v, std::vector<Vertex*>* visited) {
	if (!std::any_of(visited->begin(), visited->end(), [v](Vertex* const ver) { return ver->getId() == v->getId(); })) {
		visited->push_back(v);
		for (Vertex* ver : adjacentVertices(v)) {
			dfs(ver, visited);
		}
	}
}

// Vertex function/constructor definitions

Vertex::Vertex(Territory* t, std::string id)
	: t(t), id(id) { }

Vertex::Vertex()
	: id(""), t(nullptr) { }

std::string Vertex::getId() {
	return this->id;
}

Territory* Vertex::getTerritory() {
	return this->t;
}

bool Vertex::compare(Vertex* v) {
	return this->id == v->getId();
}

// Edge function/constructor definitions

Edge::Edge(Vertex* v1, Vertex* v2, std::string id)
	: v1(v1), v2(v2), id(id) { }

Edge::Edge()
	: id(""), v1(nullptr), v2(nullptr) { }

std::string Edge::getId() {
	return this->id;
}

std::vector<Vertex*> Edge::getEndpoints() {
	return { this->v1, this->v2 };
}

// Territory function/constructor definitions

Territory::Territory(std::string name, std::string c)
	: name(name), owner(""), armies(0), c(c) { }

Territory::Territory(Territory* t)
	: name(t->getName()), owner(t->getOwner()), armies(t->getArmies()), c(t->getContinent()) { }

Territory::Territory()
	: name(""), owner(""), armies(0), c("") { }

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

std::string Territory::getContinent() {
	return this->c;
}

std::string Territory::toString() {
	return "Name: " + this->name + "\nOwner: " + this->owner + "\nArmies: " + std::to_string(this->armies) + "\nContinent: " + this->c;
}
