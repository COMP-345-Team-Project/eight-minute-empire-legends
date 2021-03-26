#pragma once

#include "../../Core/GameCore/GameCore.h"
#include "../../Core/MapLoader/MapLoader.h"

#include "A2MainLoopTests.h"

void A2MainLoop::Test() {

	Map* map = MapLoader::parseMap("./Resources/narrows.json");

	//Game* validGame = GameBuilder::buildForMainLoop(*map, false);
	Game* validGame = GameBuilder::buildGame(2, *map);
	validGame->startUp();

	//int result = (map != NULL && map->validate() && validGame != NULL) ? 0 : 1;






	//End of demo
	delete map;
}