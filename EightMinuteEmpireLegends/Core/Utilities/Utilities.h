#pragma once
#include "../Map/map.h"
#include "../Cards/Cards.h"

Vertex* findVertexById(Map* map, std::string id);
void listActions(Card* card);
bool confirm();