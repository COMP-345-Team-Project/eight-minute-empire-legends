#pragma once
#include "../../Core/Map/Map.h"
#include "../../Core/MapLoader/MapLoader.h"

class MapLoaderTests
{
public:
	int Test_LoadValidMap_Successful();
	int Test_LoadValidMap2_Successful();
	int Test_LoadIncorrectFileFormat_ReturnsNullPointer();
	int Test_LoadJsonMissingContinents_WhatShouldHappen();
	int Test_LoadJsonMissingVertices_WhatShouldHappen();
	int Test_LoadJsonWrongDataType_WhatShouldHappen();
	int Test_LoadJsonDisconnectedGraph_WhatShouldHappen();
};