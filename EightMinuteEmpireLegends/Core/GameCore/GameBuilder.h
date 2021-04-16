#pragma once
#include "GameCore.h"

//We use a GameBuilder to create a new game object instead of initializing the Game object directly
class GameBuilder {
public:
    static Game* build();
    static Game* build(int numPlayers, std::vector<std::string> names, std::string mapPath, std::string configPath = "");
};

std::tuple<int, int, int> fetchConfigResources(std::string path);
std::vector<filesystem::path> fetchMapFiles(std::string path);
