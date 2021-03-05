#pragma once
#include "Map.h"

std::string vertices_toString(std::vector<Vertex*> v);

std::string territories_toString(std::vector<Vertex*> v);

std::string edges_toString(std::vector<Edge*> v);

std::string continents_toString(std::vector<Continent*> c);

std::string continents_toString(Map* m);
