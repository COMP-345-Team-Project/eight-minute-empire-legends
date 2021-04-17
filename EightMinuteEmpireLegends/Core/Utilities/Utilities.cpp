#include "../pch.h"
#include "Utilities.h"
#include <vector>
#include "../Map/Map.h"
#include "../Player/Player.h"

Vertex* findVertexById(Map* map, string id) {
	vector<Vertex*> vertices = map->vertices();
	for (vector<Vertex*>::iterator vertexIter = vertices.begin(); vertexIter != vertices.end(); vertexIter++) {
		if ((**vertexIter).getId().compare(id) == 0)
			return *vertexIter;
	}
}

void listActions(Card* card) {
	std::string firstAction = card->getFirstAction();
	std::string secondAction = card->getSecondAction();
	std::cout << "The available action(s) is/are: " << std::endl;

	//If we have 2 actions
	if (secondAction.compare("") != 0) {
		std::cout << "1. ";
		card->printHelper(card->getFirstAction());
		std::cout << std::endl;

		std::cout << "2. ";
		card->printHelper(card->getSecondAction());
		std::cout << std::endl;

		if (card->getAndAction()) //And action
			std::cout << "You can perform both actions." << std::endl;
		else //Or action
			std::cout << "You can perform only one of the actions. Please select one of them." << std::endl;
	}
	else { //We only have 1 actions
		std::cout << "1. ";
		card->printHelper(card->getFirstAction());
		std::cout << std::endl;
	}
}

bool confirm() {
	char confirm;
	do {
		std::cin >> confirm;
		if (confirm == 'N') {
			return false;
		}
		else if (confirm == 'Y') {
			return true;
		}
		else {
			std::cout << "Please enter Y for yes or N for no";
		}
	} while (true);
}