#pragma once
#include "MapLoader.h"
#include "Map.h"
#include <fstream>
#include <iostream>
#include "json.hpp"

using std::string;
using std::vector;
using json = nlohmann::json;
using std::cout;

MapLoader::MapLoader() {

}

bool MapLoader::validateMap(std::string path) {
	std::ifstream fileContentStream(path);
	bool isValid = json::accept(fileContentStream);

	if (!isValid) {
		std::cout << "The file is not a valid json file.\n";
	}

	return isValid;
}

Map MapLoader::parseMap(string path) {

	std::ifstream fileContentStream(path);
	json mapJson = json::parse(fileContentStream);
	//std::cout << mapJson.dump() + "\n";

	try {
		/*json jsonContinents = mapJson["continentVertices"];
		int numOfContinents = static_cast<int>(jsonContinents.size());

		for (int i = 0; i < numOfContinents; i++) {
			json jsonContinent = jsonContinents[i];
			string continentName = jsonContinent["name"];
			std::cout << "Continent name is " + continentName + "\n";

			json jsonVertices = jsonContinent["vertices"];
			int numOfVertices = static_cast<int>(jsonVertices.size());
			//Need a dynamic array because the number of vertices are not known at compile time
			vector<Vertex*> vertices;

			for (int j = 0; j < numOfVertices; j++) {
				auto jsonVertex = jsonVertices[j];
				Territory territory(jsonVertex["territory"]); //Need another constructor
				string vertexId = jsonVertex["id"].dump();
				Vertex *vertex = new Vertex(&territory, vertexId);
				vertices.push_back(vertex);
				std::cout << vertexId + "\n";
			}

			json jsonEdges = jsonContinent["edges"];
			int numOfEdges = static_cast<int>(jsonEdges.size());
			//Need a dynamic array because the number of vertices are not known at compile time
			vector<Edge*> edges;

			for (int j = 0; j < numOfVertices; j++) {
				auto jsonEdge = jsonEdges[j];
				string vertexId1 = jsonEdge["v1"];
				string vertexId2 = jsonEdge["v2"];
				Vertex *vertex1 = NULL;
				Vertex *vertex2 = NULL;

				for (int k = 0; k < numOfVertices; k++)
				{
					Vertex* currentVertex = vertices.at(k);
					if (currentVertex->getId().compare(vertexId1))
						vertex1 = currentVertex;
					else if (currentVertex->getId().compare(vertexId2))
						vertex2 = currentVertex;
				}

				if (vertex1 != NULL && vertex2 != NULL) {
					string edgeId = jsonEdge["id"];
					Edge* edge = new Edge(vertex1, vertex2, edgeId);
					edges.push_back(edge);
				}
			}
		}*/

		//Create the list of continents first
		json jsonContinents = mapJson["continents"];
		int numOfContinents = static_cast<int>(jsonContinents.size());
		vector<Continent*> continents;

		for (int i = 0; i < numOfContinents; i++) {
			auto jsonContinent = jsonContinents[i];
			string continentName = jsonContinent["name"].dump();

			Continent continent(continentName);
			Continent* continentPtr = &continent;
			continents.push_back(continentPtr);
		}

		//Create the list of vertices and their correspoding territories
		json jsonVertices = mapJson["vertices"];
		int numOfVertices = static_cast<int>(jsonVertices.size());
		vector<Vertex*> vertices;

		for (int j = 0; j < numOfVertices; j++) {
			auto jsonVertex = jsonVertices[j];
			string id = jsonVertex["id"].dump();
			string territoryName = jsonVertex["territoryName"].dump();
			string continentName = jsonVertex["continentName"].dump();

			Continent* continentPtr = getContinentByName(continents, continentName);
			if (continentPtr == NULL)
				throw "The continent with the name <<" + continentName + "does not exist";

			Territory territory(territoryName, continentPtr); 
			Territory* territoryPtr = &territory;
			Vertex vertex(territoryPtr, id);

			Vertex* vertexPtr = &vertex;
			vertices.push_back(vertexPtr);
		}

		//Parse the edges
		json jsonEdges = mapJson["edges"];
		int numOfEdges = static_cast<int>(jsonEdges.size());
		//Need a dynamic array because the number of vertices are not known at compile time
		vector<Edge*> edges;

		for (int j = 0; j < numOfVertices; j++) {
			auto jsonEdge = jsonEdges[j];
			string vertexId1 = jsonEdge["v1"];
			string vertexId2 = jsonEdge["v2"];
			Vertex* vertex1 = NULL;
			Vertex* vertex2 = NULL;

			for (int k = 0; k < numOfVertices; k++)
			{
				Vertex* currentVertex = vertices.at(k);
				if (currentVertex->getId().compare(vertexId1))
					vertex1 = currentVertex;
				else if (currentVertex->getId().compare(vertexId2))
					vertex2 = currentVertex;
			}

			if (vertex1 != NULL && vertex2 != NULL) {
				string edgeId = jsonEdge["id"];
				Edge* edge = new Edge(vertex1, vertex2, edgeId);
				edges.push_back(edge);
			}
			else {
				throw "The vertex with the id <<" + vertexId1 + ">> or <<" + vertexId2 + ">> does not exist";
			} 
		}

		return NULL;

	}
	catch (string message) {
		std::cout << message;
	}
}

Continent* MapLoader::getContinentByName(vector<Continent*> &continents, string &name) {
	Continent* continent = NULL;
	for (int i = 0; i < continents.size() && continent == NULL; i++) {
		Continent* currContinent = continents.at(i);
		if (currContinent->getName().compare(name) == 0)
			continent = currContinent;
	}

	return continent;
}




