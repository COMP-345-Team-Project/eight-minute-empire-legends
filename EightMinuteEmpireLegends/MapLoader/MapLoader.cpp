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

Map* MapLoader::parseMap(string path) {
	Map* mapPtr = NULL;

	//Make sure that we have a json file
	if (validateMap(path)) {
		std::ifstream fileContentStream(path);
		json mapJson = json::parse(fileContentStream);

		try {
			//Create the list of continents first
			json jsonContinents = mapJson["continents"];
			int numOfContinents = static_cast<int>(jsonContinents.size());

			vector<Continent*> continents;

			for (int i = 0; i < numOfContinents; i++) {
				auto jsonContinent = jsonContinents[i];
				string continentName = jsonContinent["name"].get<std::string>();
				//std::cout << "Continent name: " + continentName << std::endl;

				Continent* continentPtr = new Continent();
				continentPtr->name = continentName;

				continents.push_back(continentPtr);
			}

			//Create the map with the continents
			string mapName = mapJson["name"];
			Map map(mapName, continents);

			//Create the list of vertices and their correspoding territories
			json jsonVertices = mapJson["vertices"];
			int numOfVertices = static_cast<int>(jsonVertices.size());
			//vector<Vertex*> vertices;

			for (int j = 0; j < numOfVertices; j++) {
				auto jsonVertex = jsonVertices[j];
				string id = jsonVertex["id"].get<std::string>();
				string territoryName = jsonVertex["territoryName"].get<std::string>();
				string continentName = jsonVertex["continentName"].get<std::string>();

				Continent* continentPtr = getContinentByName(continents, continentName);
				if (continentPtr == NULL)
					throw "The continent with the name <<" + continentName + ">> does not exist";

				Territory* territory = new Territory(territoryName, continentName);
				Vertex* vertex = new Vertex(territory, id);

				map.insertVertex(vertex);
			}

			//Parse the edges
			json jsonEdges = mapJson["edges"];
			int numOfEdges = static_cast<int>(jsonEdges.size());
			//Need a dynamic array because the number of vertices are not known at compile time

			for (int j = 0; j < numOfEdges; j++) {
				auto jsonEdge = jsonEdges[j];
				string vertexId1 = jsonEdge["v1"].get<std::string>();
				string vertexId2 = jsonEdge["v2"].get<std::string>();
				Vertex* vertex1 = NULL;
				Vertex* vertex2 = NULL;

				Vertex* currentVertex = NULL;
				for (int k = 0; k < map.vertices().size(); k++)
				{
					currentVertex = map.vertices().at(k);
					if (currentVertex->getId().compare(vertexId1) == 0)
						vertex1 = currentVertex;
					else if (currentVertex->getId().compare(vertexId2) == 0)
						vertex2 = currentVertex;
				}

				if (vertex1 != NULL && vertex2 != NULL) {
					string edgeId = jsonEdge["id"].get<std::string>();
					Edge* edge = new Edge(vertex1, vertex2, edgeId);
					map.insertEdge(edge);
				}
				else {
					throw "The vertex with the id <<" + vertexId1 + ">> or <<" + vertexId2 + ">> does not exist";
				}
			}

			/*bool isValid = map.validate();
			if (!isValid) {
				throw "The map is not a valid graph";
			}
			else {
				std::cout << "The map is a valid graph" << std::endl;
			}*/

			mapPtr = &map;
		}
		catch (string message) {
			std::cout << message << std::endl;
		}
		catch (json::exception& e) {
			std::cout << "A nlohmann json parser error occured. Make sure your json is valid and have the correct structure." << std::endl;
		}
	}

	if (mapPtr == NULL)
		mapPtr = new Map();

	return mapPtr;
}

Continent* MapLoader::getContinentByName(vector<Continent*> &continents, string &name) {
	Continent* continent = NULL;
	for (std::vector<Continent*>::iterator it = continents.begin(); it != continents.end(); ++it) {
		Continent* currContinent = (*it);
		if (currContinent->name.compare(name) == 0) {
			return currContinent;
		}
	}
}




