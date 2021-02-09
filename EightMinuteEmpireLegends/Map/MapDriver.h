#pragma once
#include <string>
#include <vector>
#include "Map.h"

std::string vertices_toString(std::vector<Vertex*> v) {
	std::string str = "Vertices: [ ";

	for (Vertex* ver : v) {
		str += ver->getId() + " ";
	}
	return str + "]";
}

std::string edges_toString(std::vector<Edge*> v) {
	std::string str = "Edges: [ ";

	for (Edge* ed : v) {
		str += ed->getId() + " ";
	}
	return str + "]";
}