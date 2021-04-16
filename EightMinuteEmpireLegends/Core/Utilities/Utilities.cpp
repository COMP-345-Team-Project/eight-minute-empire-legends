#include "../pch.h"
#include <vector>
#include "../Map/Map.h"
#include "../Player/Player.h"

void displayTerritories(std::vector<Vertex*> vertices, bool numbered, std::vector<Player*> player, Player* neutralPlayer) {
	int number = 0;
	for (Vertex* v : vertices) {
		if (numbered) {
			std::cout << "\n( " << number++ << " ) -------------------------" << std::endl;
		}
		else {
			std::cout << "\n-------------------------------" << std::endl;
		}
		std::cout << "      Territory :      " << v->getTerritory()->getName() << std::endl;
		std::cout << "      Owner :          " << v->getTerritory()->getOwner() << std::endl;
		std::cout << "      Continent :      " << v->getTerritory()->getContinent() << std::endl;
		if (neutralPlayer != nullptr) {
			std::cout << "      Neutral Armies : " << v->getTerritory()->getArmiesByPlayer(neutralPlayer->getPlayerName()) << std::endl;
		}
		std::cout << "  --- Armies ---" << std::endl;
		for (Player* pl : player) {
			std::cout << "      " << pl->getPlayerName() << " - " << v->getTerritory()->getArmiesByPlayer(pl->getPlayerName()) << std::endl;
		}

		std::cout << "  --- Cities ---" << std::endl;
		for (Player* pl : player) {
			std::cout << "      " << pl->getPlayerName() << " - " << v->getTerritory()->getCitiesByPlayer(pl->getPlayerName()) << std::endl;
		}
		std::cout << std::endl;
	}
}

void displayPlayerStats(Player* currPlayer, Map* map, vector<Player*> players) {
	std::cout << "------Player stats------" << std::endl;
	std::cout << "Player name: " << currPlayer->getPlayerName() << std::endl;
	std::cout << "Available coins: " << currPlayer->getCoins() << std::endl;
	std::cout << "Available armies: " << currPlayer->getAvailableArmies() << std::endl;
	std::cout << "Available cities: " << currPlayer->getAvailableCities() << std::endl;
	std::cout << "Regions owned: ";
	/*vector<string> ownedRegions = currPlayer->GetOwnedRegions();
	for (int i = 0; i < ownedRegions.size(); i++) {
		std::cout << ownedRegions[i] << "\t";
	}*/
	std::cout << endl;
	std::cout << "Victory points: " << currPlayer->ComputeScore(map, players) << std::endl;
}

Vertex* findVertexById(Map* map, string id) {
	vector<Vertex*> vertices = map->vertices();
	for (vector<Vertex*>::iterator vertexIter = vertices.begin(); vertexIter != vertices.end(); vertexIter++) {
		if ((**vertexIter).getId().compare(id) == 0)
			return *vertexIter;
	}
}