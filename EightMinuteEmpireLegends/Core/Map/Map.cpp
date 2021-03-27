#pragma once
#include "../pch.h"

#include "./Map.h"

// Map function/constructor definitions

Map::Map(std::string name, std::vector<Continent*> c)
	: name(name), v_vertices({}), v_edges({}), v_continents(c), startingRegion(nullptr) { }

Map::Map(const Map& m)
	: name(m.name), v_vertices(m.v_vertices), v_edges(m.v_edges), v_continents(m.v_continents) {
	if (m.startingRegion != nullptr) {
		this->startingRegion = new Vertex(*m.startingRegion);
	}	
}

Map::Map()
	: name(""), v_vertices({}), v_edges({}), v_continents({}), startingRegion(nullptr) { }

Map::~Map() {
	for (Edge* ed : this->edges()) {
		delete ed;
		ed = NULL;
	}

	for (Vertex* ver : this->vertices()) {
		delete ver;
		ver = NULL;
	}

	for (Continent* con : this->continents()) {
		delete con;
		con = NULL;
	}
}

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

	this->v_edges.erase(std::remove_if(begin, end,
		[id](Edge* const e) {
			return (e->getEndpoints()[0]->getId() == id || e->getEndpoints()[1]->getId() == id);
		}), end);
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
	if (this->v_vertices.size() > 0) {
		std::vector<Vertex*> visited{};
		Vertex* first = this->v_vertices.at(0);
		dfs(first, &visited);
		return (visited.size() == this->v_vertices.size() && this->v_continents.size() > 1);
	}
	return false;
}

void Map::dfs(Vertex* v, std::vector<Vertex*>* visited) {
	if (!std::any_of(visited->begin(), visited->end(),
		[v](Vertex* const ver) {
			return ver->getId() == v->getId();
		})) {
		visited->push_back(v);
		for (Vertex* ver : adjacentVertices(v)) {
			dfs(ver, visited);
		}
	}
}

Map& Map::operator =(const Map& m) {
	this->name = m.name;
	this->v_vertices = m.v_vertices;
	this->v_edges = m.v_edges;
	this->v_continents = m.v_continents;
	this->startingRegion = new Vertex(*m.startingRegion);

	return *this;
}

std::ostream& operator <<(std::ostream& os, const Map* m) {	
	os << "Map : " << m->name << std::endl;
	os << "Vertices: [" << std::endl;
	for (Vertex* v : const_cast<Map*>(m)->vertices()) {		
		os << v << std::endl;
	}
	os << "]\n" << "Edges : [" << std::endl;
	for (Edge* e : const_cast<Map*>(m)->edges()) {
		os << e << std::endl;
	}
	os << "]\n" << "Continents : [" << std::endl;
	for (Continent* c : const_cast<Map*>(m)->continents()) {
		os << c << std::endl;
	}
	os << "]\n" << "Starting Region : ";
	m->startingRegion != nullptr ? os << m->startingRegion : os << "None";
	
	return os;
}

// Continent assignment operator definition

std::ostream& operator <<(std::ostream& os, const Continent* c) {
	os << c->name;

	return os;
}

// Vertex function/constructor definitions

Vertex::Vertex(Territory* t, std::string id)
	: t(t), id(id) { }

Vertex::Vertex(const Vertex& v)
	: t(new Territory(*v.t)), id(v.id) { }

Vertex::Vertex()
	: id(""), t(nullptr) { }


Vertex::~Vertex() {
	delete t;
}

std::string Vertex::getId() {
	return this->id;
}

Territory* Vertex::getTerritory() {
	return this->t;
}

bool Vertex::compare(Vertex* v) {
	return this->id == v->getId();
}

Vertex& Vertex::operator =(const Vertex& v) {
	this->id = v.id;

	return *this;
}

std::ostream& operator <<(std::ostream& os, const Vertex* v) {
	os << "Vertex ID: " + v->id << "\nTerritory {\n" << v->t << "\n}";
	return os;
}

// Edge function/constructor definitions

Edge::Edge(Vertex* v1, Vertex* v2, std::string id)
	: v1(v1), v2(v2), id(id) { }

Edge::Edge(const Edge& e)
	: id(e.id), v1(new Vertex(*e.v1)), v2(new Vertex(*e.v2)) { }

Edge::Edge()
	: id(""), v1(nullptr), v2(nullptr) { }

std::string Edge::getId() {
	return this->id;
}

std::vector<Vertex*> Edge::getEndpoints() {
	return { this->v1, this->v2 };
}

Edge& Edge::operator =(const Edge& e) {
	this->id = e.id;
	this->v1 = new Vertex(*e.v1);
	this->v2 = new Vertex(*e.v2);

	return *this;
}

std::ostream& operator <<(std::ostream& os, const Edge* e) {
	os << "Edge ID: " + e->id << "\nVertex 1 {\n" << e->v1 << "\n}" << "\nVertex 2 {\n" << e->v2;
	return os;
}

// Territory function/constructor definitions

Territory::Territory(std::string name, std::string continent)
	: name(name), continent(continent) { }

Territory::Territory(const Territory& t)
	: name(t.name), continent(t.continent), armies(t.armies), cities(t.cities) {
}

Territory::Territory()
	: name(""), continent("") { }

void Territory::setName(std::string name) {
	this->name = name;
}

void Territory::setArmiesByPlayer(int armies, std::string playerName) {
	std::map<std::string, int>::iterator it;
	it = this->armies.find(playerName);

	if (it == this->armies.end())
		this->armies.insert(std::pair<std::string, int>(playerName, armies));
	else
		this->armies[playerName] = armies;
}

void Territory::setCitiesByPlayer(int cities, std::string playerName) {
	std::map<std::string, int>::iterator it;
	it = this->cities.find(playerName);

	if (it == this->cities.end())
		this->cities.insert(std::pair<std::string, int>(playerName, cities));
	else
		this->cities[playerName] = cities;
}

std::string Territory::getName() {
	return this->name;
}

std::string Territory::getOwner() {
	//return this->owner;
	if (armies.size() > 0) {
		std::map<std::string, int>::iterator owner = std::max_element(armies.begin(), armies.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b)->bool { return a.second < b.second; });
		std::string ownerName = owner->first;
		int ownerArmies = owner->second;

		//We also need to make sure there is no player with the same maximum value
		for (std::map<std::string, int>::iterator mapIter = armies.begin(); mapIter != armies.end(); mapIter++) {
			if (mapIter->first.compare(ownerName) != 0 && mapIter->second == ownerArmies)
				return "";
		}

		return ownerName;
	}
	
	return "";
}

int Territory::getArmiesByPlayer(std::string playerName) {
	std::map<std::string, int>::iterator it;
	it = this->armies.find(playerName);

	if (it == this->armies.end())
		return 0;
	else
		return this->armies[playerName];
}

int Territory::getCitiesByPlayer(std::string playerName) {
	std::map<std::string, int>::iterator it;
	it = this->cities.find(playerName);

	if (it == this->cities.end())
		return 0;
	else
		return this->cities[playerName];
}

void Territory::addArmiesByPlayer(int armies, std::string playerName) {
	int newNumOfArmies = getArmiesByPlayer(playerName) + armies;
	setArmiesByPlayer(newNumOfArmies, playerName);
}

void Territory::destroyArmiesByPlayer(int armies, std::string playerName) {
	int newNumOfArmies = getArmiesByPlayer(playerName) - armies;
	setArmiesByPlayer(newNumOfArmies, playerName);
}

void Territory::addCitiesByPlayer(int cities, std::string playerName) {
	int newNumOfCities = getCitiesByPlayer(playerName) + cities;
	setCitiesByPlayer(newNumOfCities, playerName);
}

std::string Territory::getContinent() {
	return this->continent;
}

Territory& Territory::operator =(const Territory& t) {
	this->name = t.name;
	this->armies = t.armies;

	return *this;
}

std::ostream& operator <<(std::ostream& os, const Territory* t) {
	os << "Name: " << t->name << "\nContinent: " << t->continent;
	return os;
}
