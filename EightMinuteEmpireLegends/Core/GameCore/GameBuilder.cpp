#include "GameBuilder.h"
#include "../GameObservers/GameStatistics.h"

Game* GameBuilder::build() {
	std::vector<filesystem::path> maps = fetchMapFiles(_mapDir);
	std::vector<std::string> names{};
	std::cout << "Please select a map.\n" << std::endl;
	int index = 0;
	int mapSelection;
	int numPlayers;

	// Map selection
	for (const auto& entry : maps) {
		std::cout << index << ") " << entry.filename() << std::endl;
		index++;
	}
	std::cin >> mapSelection;
	if (mapSelection < 0 || mapSelection >= maps.size()) {
		throw GameBuilderException("ERR: Selection index out of range.");
	}

	// Player selection

	bool validNum = false;
	while (!validNum) {
		std::cout << "Please enter the number of players (2-4) : ";
		std::cin >> numPlayers;
		if (cin.fail()) {
			cin.clear();
			cin.sync();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input. Please enter an integer.\n" << std::endl;
		}
		else if (numPlayers < 2 || numPlayers > 4) {
			std::cout << "Player count selection out of range.\n" << std::endl;
		}
		else {
			validNum = true;
		}
	}
	std::string plName;
	bool validName;
	for (int i = 0; i < numPlayers; i++) {
		validName = false;
		while (!validName) {
			std::cout << "Please enter a name for player " + i << " : ";
			std::cin >> plName;
			if (std::find(names.begin(), names.end(), plName) != names.end()) {
				std::cout << "Name has already been taken by another player. Please enter a unique name." << std::endl;
			}
			else {
				validName = true;
			}
		}
		names.push_back(plName);
	}

	return build(numPlayers, names, maps.at(mapSelection).u8string(), _configPath);
}

Game* GameBuilder::build(int numPlayers, std::vector<std::string> names, std::string mapPath, std::string configPath) {
	Resources* rsc = nullptr;
	Map* map = nullptr;

	// Initiallize resources if path to config is specified		
	if (configPath != "") {
		std::tuple<int, int, int> tResources;
		try {
			tResources = fetchConfigResources(configPath);
			rsc = new Resources(std::get<0>(tResources), std::get<1>(tResources), std::get<2>(tResources));
		}
		catch (ConfigFileException& e) {
			std::cout << "Uh oh! Configuration file not found. Resources will use default values." << std::endl << e.what() << std::endl;
			tResources = std::make_tuple(_dCoins, _dArmies, _dCities);
		}
	}
	else {
		//Initiallize resources to default parameters if path to config is not specified
		rsc = new Resources();
	}

	try {
		map = MapLoader::parseMap(mapPath);
	}
	catch (MapLoaderException& e) {
		std::cout << e.what() << std::endl;
	}

	Deck* deck = new Deck(numPlayers);
	BidTieBreakerByLastName tieBreaker;
	BiddingFacility* bf = new BiddingFacility(tieBreaker);
	std::vector<Player*> pl{};
	for (int i = 0; i < numPlayers; i++) {
		pl.push_back(new Player(names.at(i), bf));
	}

	//Use PlayerBuilder to set player type (Computer or Human)


	//Create the game and attach Observer
	Game* newGame = new Game(rsc, map, deck, pl);
	GameStatistics* gameStatsObserver = new GameStatistics(newGame); //THe observer attach it self to the game

	//Crete a new game object and pass above objects to Game
	return newGame;
}

// Helper function. Reads resources from config file.
std::tuple<int, int, int> fetchConfigResources(std::string path) {
	int coins;
	int armies;
	int cities;
	std::string line;
	char delim = '=';
	std::ifstream rFile(path);
	if (rFile.is_open()) {
		while (getline(rFile, line)) {
			if (line.substr(0, line.find(delim)) == "rCoins") {
				coins = std::stoi(line.substr(line.find(delim) + 1));
			}
			if (line.substr(0, line.find(delim)) == "rArmies") {
				armies = std::stoi(line.substr(line.find(delim) + 1));
			}
			if (line.substr(0, line.find(delim)) == "rCities") {
				cities = std::stoi(line.substr(line.find(delim) + 1));
			}
		}
		rFile.close();
	}
	else {
		throw ConfigFileException("ERR: Unable to open file at " + path);
	}
	return std::make_tuple(coins, armies, cities);;
}

std::vector<filesystem::path> fetchMapFiles(std::string path) {
	std::vector<filesystem::path> maps{};
	for (const auto& entry : filesystem::directory_iterator(path)) {
		maps.push_back(entry.path());
	}
	return maps;
}