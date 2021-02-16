#pragma once
#include <string>
#include <vector>
#include "Map.h"

// Returns string list of a vertex vector
std::string vertices_toString(std::vector<Vertex*> v) {
	std::string str = "Vertices: [ ";

	for (Vertex* ver : v) {
		str += ver->getId() + " ";
	}
	return str + "]";
}

// Returns string list of a territory vector
std::string territories_toString(std::vector<Vertex*> v) {
	std::string str = "Territories: [ ";

	for (Vertex* ver : v) {
		str += ver->getTerritory()->getName() + " ";
	}
	return str + "]";
}

// Returns string list of an edge vector
std::string edges_toString(std::vector<Edge*> v) {
	std::string str = "Edges: [ ";

	for (Edge* ed : v) {
		str += ed->getId() + "{ " + ed->getEndpoints()[0]->getId() + ", " + ed->getEndpoints()[1]->getId() + " } ";
	}
	return str + "]";
}

// Returns string list of a continent vector
std::string continents_toString(std::vector<Continent*> c) {
	std::string str = "Continents: [ ";

	for (Continent* con : c) {
		str += con->name + " ";
	}
	return str + "]";
}

// Returns string list of a territory vector grouped by their respective continent
std::string continents_toString(Map* m) {
	std::string str = "Comprehensive: [ ";

	for (Continent* con : m->continents()) {
		str += con->name + ": [ " + territories_toString(m->vertices(con)) + "] ";
	}
	return str + "]";
}