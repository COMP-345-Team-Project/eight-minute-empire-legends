#pragma once
#include <string>
#include <vector>
#include "Map.h"

using namespace std;

string vertices_toString(vector<Vertex> v) {
	string str = "Vertices: [ ";

	for (Vertex ver : v) {
		str += ver.getId() + " ";
	}
	return str + "]";
}

string edges_toString(vector<Edge> v) {
	string str = "Edges: [ ";

	for (Edge ed : v) {
		str += ed.getId() + " ";
	}
	return str + "]";
}