#pragma once
#include "MapLoader.h"
#include "Map.h"
#include <fstream>
#include <iostream>
#include "json.hpp"
#include <vector>

using json = nlohmann::json;
using std::cout;

MapLoader::MapLoader() {

}

bool MapLoader::validateMap(string path) {
	std::ifstream fileContentStream(path);
	bool isValid = json::accept(fileContentStream);

	if (!isValid) {
		std::cout << "The file is not a valid json file.\n";
	}

	return isValid;
}

void MapLoader::parseMap(string path) {
	std::ifstream fileContentStream(path);
	json mapJson = json::parse(fileContentStream);
	//std::cout << mapJson.dump() + "\n";

	try {
		json jsonContinents = mapJson["continentVertices"];
		int numOfContinents = static_cast<int>(jsonContinents.size());

		for (int i = 0; i < numOfContinents; i++) {
			json jsonContinent = jsonContinents[i];
			string continentName = jsonContinent["name"];
			std::cout << "Continent name is " + continentName + "\n";

			json jsonVertices = jsonContinent["vertices"];
			int numOfVertices = static_cast<int>(jsonVertices.size());
			//Need a dynamic array because the number of vertices are not known at compile time
			vector<Vertex> vertices;

			for (int j = 0; j < numOfVertices; j++) {
				auto jsonVertex = jsonVertices[j];
				Territory territory(jsonVertex["territory"], "a"); //Need another constructor
				string vertexId = jsonVertex["id"].dump();
				Vertex vertex(territory, vertexId);
				vertices.push_back(vertex);
				std::cout << vertexId + "\n";
			}
		}
	}
	catch(string message){
		std::cout << message;
	}
	

	/*auto jsonVertices = mapJson["continentVertices"][0]["vertices"];
	
	
	for (int i = 0; i < numOfVertices; i++) {
		auto jsonVertex = jsonVertices[i];
		Territory territory(jsonVertex["territory"], "a"); //Need another constructor
		Vertex vertex(territory, jsonVertex["id"]);
		vertices.push_back(vertex);
	}

	for (int i = 0; i < numOfVertices; i++) {
		std::cout << vertices.at(i).getId();
	}*/
}

