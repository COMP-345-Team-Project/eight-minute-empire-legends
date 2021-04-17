#include "GameStatisticsTests.h"
#include "../../Core/Utilities/Utilities.h"
#include "../../Core/Player/Player.h"
#include "../../Core/GameCore/GameCore.h"
#include "../../Core/GameCore/GameBuilder.h"
#include "../../Core/GameObservers/GameStatistics.h"
#include "../../Core/Bidding/BidTieBreakerByLastName.h"
#include "../../Core/MapLoader/MapLoader.h"

GameStatisticsTests::GameStatisticsTests() {
	numOfArmiesToDeploy = 1;
	badNumOfArmiesToDeploy = 0;
	numOfCoins = 11;
	numOfArmies = 10;
	numOfCities = 3;
	playerName = "player1";
	altPlayerName = "player2";
	//Temporary fix for the running directory issue, will be removed after
	mapPath = "../Tests/MapLoaderTests/Resources/validJson_validMap.json";
}

void GameStatisticsTests::Test_PrintPlayerStats() {
	std::cout << "\nTesting Player::Testing Game Statistics Observer()" << std::endl;

	vector<std::string> playerNames = { playerName, altPlayerName };
	Game* game = GameBuilder::build(2, playerNames, mapPath, "");

	GameStatistics gameStatsObserver(game);

	Player* p1 = game->getPlayers().at(0);
	Player* p2 = game->getPlayers().at(1);
	p1->InitResources(numOfCoins, numOfArmies, numOfCities);
	p2->InitResources(numOfCoins, numOfArmies, numOfCities);

	Map* map = game->getMap();

	//Set the starting region1
	//Regions from Continent 1
	Vertex* v0 = findVertexById(map, "0");
	Vertex* v1 = findVertexById(map, "1");
	Vertex* v2 = findVertexById(map, "2");
	Vertex* v3 = findVertexById(map, "3");
	Vertex* v4 = findVertexById(map, "4");
	Vertex* v5 = findVertexById(map, "5"); //tie region
	//Regions from Continent 2
	Vertex* v6 = findVertexById(map, "6");
	Vertex* v7 = findVertexById(map, "7");
	//Regions from Continent 3
	Vertex* v10 = findVertexById(map, "10");
	Vertex* v11 = findVertexById(map, "11");
	//Regions from Continent 4, tie continent
	Vertex* v13 = findVertexById(map, "13");
	Vertex* v14 = findVertexById(map, "14");
	//map->setStartingRegion(v1);

	//Assign some regions to the players directly (bypassing Place armies to avoid game logic)
	//p1 owns 3 regions from continent 1, 2 from continent 2, 1 from continent 4 => Owns 2 continent
	v0->getTerritory()->setArmiesByPlayer(1, p1->getPlayerName());
	v1->getTerritory()->setArmiesByPlayer(1, p1->getPlayerName());
	v2->getTerritory()->setArmiesByPlayer(2, p1->getPlayerName());
	v5->getTerritory()->setArmiesByPlayer(1, p1->getPlayerName());
	v6->getTerritory()->setArmiesByPlayer(1, p1->getPlayerName());
	v7->getTerritory()->setArmiesByPlayer(1, p1->getPlayerName());
	v13->getTerritory()->setArmiesByPlayer(1, p1->getPlayerName());

	//p2 owns 2 regions from continent 1, 2 from continent 3, 1 from continent 4 => Owns 1 continent
	v2->getTerritory()->setArmiesByPlayer(1, p2->getPlayerName());
	v3->getTerritory()->setArmiesByPlayer(1, p2->getPlayerName());
	v4->getTerritory()->setArmiesByPlayer(1, p2->getPlayerName());
	v5->getTerritory()->setArmiesByPlayer(1, p2->getPlayerName());
	v10->getTerritory()->setArmiesByPlayer(1, p2->getPlayerName());
	v11->getTerritory()->setArmiesByPlayer(1, p2->getPlayerName());
	v14->getTerritory()->setArmiesByPlayer(1, p2->getPlayerName());

	//Add the deployed armies to the player list of deployed regions
	p1->AddDeployedVertex(v0);
	p1->AddDeployedVertex(v1);
	p1->AddDeployedVertex(v2);
	p1->AddDeployedVertex(v5);
	p1->AddDeployedVertex(v6);
	p1->AddDeployedVertex(v7);
	p1->AddDeployedVertex(v13);
	p2->AddDeployedVertex(v2);
	p2->AddDeployedVertex(v3);
	p2->AddDeployedVertex(v4);
	p2->AddDeployedVertex(v5);
	p2->AddDeployedVertex(v10);
	p2->AddDeployedVertex(v11);

	//Build some cities, 1 city per player
	//v13->getTerritory()->setCitiesByPlayer(1, playerName);
	p1->BuildCity(v13, 1);
	//v14->getTerritory()->setCitiesByPlayer(1, altPlayerName);
	p2->BuildCity(v14, 1);

	//Setting up the cards for player 1: 4 ancient cards, 3 nobel cards
	Card* card1 = new Card("Ancient Phoenix", 0, 5, 0, 0, "moveArmy", "", false, 0, 0, true, 0, 0, "");
	Card* card2 = new Card("Ancient Sage", 0, 3, 0, 0, "moveArmy", "", false, 0, 0, false, 0, 0, "1VPperAncient");
	Card* card3 = new Card("Ancient Tree Spirit", 4, 0, 0, 0, "newArmy", "", false, 0, 0, false, 3, 0, "");
	Card* card4 = new Card("Ancient Woods", 1, 0, 1, 0, "buildCity", "newArmy", true, 0, 1, false, 0, 0, "");
	Card* card5 = new Card("Noble Hills", 3, 0, 0, 0, "newArmy", "", false, 0, 0, false, 0, 0, "3NobleCards=4VP");
	Card* card6 = new Card("Noble Knight", 4, 0, 0, 1, "newArmy", "destroyArmy", true, 1, 0, false, 0, 0, "");
	Card* card7 = new Card("Noble Unicorn", 1, 4, 0, 0, "moveArmy", "newArmy", true, 1, 0, false, 0, 0, "");

	p1->addCard(card1);
	p1->addCard(card2);
	p1->addCard(card3);
	p1->addCard(card4);
	p1->addCard(card5);
	p1->addCard(card6);
	p1->addCard(card7);

	p1->addElixirs(card3->getElixer()); //Cards 3 has 3 elixir

	//Setting up the cards for player 2: 4 ancient cards, 3 nobel cards
	Card* card8 = new Card("Dire Dragon", 3, 0, 0, 1, "newArmy", "destroyArmy", true, 0, 0, true, 0, 0, "");
	Card* card9 = new Card("Dire Eye", 4, 0, 0, 0, "newArmy", "", false, 0, 0, true, 0, 0, "");
	Card* card10 = new Card("Dire Giant", 3, 0, 0, 1, "newArmy", "destroyArmy", true, 0, 0, false, 0, 0, "immuneToAttack");
	Card* card11 = new Card("Dire Goblin", 0, 5, 0, 0, "moveArmy", "", false, 0, 0, false, 1, 0, "");
	Card* card12 = new Card("Dire Ogre", 0, 2, 0, 0, "moveArmy", "", false, 0, 0, false, 0, 0, "1VPper3Coins");
	Card* card13 = new Card("Stronghold", 0, 0, 1, 0, "buildCity", "", false, 0, 0, false, 0, 0, "1VPperDireCard");

	p2->addCard(card8);
	p2->addCard(card9);
	p2->addCard(card10);
	p2->addCard(card11);
	p2->addCard(card12);
	p2->addCard(card13);

	p2->addElixirs(card11->getElixer()); //Cards 11 has 1 elixir

	//Compute the score 
	vector<Player*> players{ p1, p2 };
	p1->ComputeScore(map, players);
	p2->ComputeScore(map, players);
	

	//Some assertions before printing out, we bypassed some of the game mechanism so we just have to compare the original values
	PlayerScore playerScore = p1->getPlayerScore();
	vector<string> p1OwnedTerritories{
		v0->getTerritory()->getName(),
		v1->getTerritory()->getName(),
		v2->getTerritory()->getName(),
		v6->getTerritory()->getName(),
		v7->getTerritory()->getName(),
		v13->getTerritory()->getName()
	};
	vector<string> p1OwnedContinents = {
		"continent1",
		"continent2"
	};
	vector<string> p1Abilities = {
		"1VPperAncient",
		"3NobleCards=4VP"
	};

	assert(p1->getCoins() == numOfCoins);
	assert(p1->getAvailableArmies() == numOfArmies);
	assert(p1->getAvailableCities() == (numOfCities-1));
	assert(p1->getCards().size() == 7);
	assert(playerScore.getTerritoryScore() == 6);
	assert(playerScore.getContinentScore() == 2);
	assert(playerScore.getAbilityScore() == 8);
	assert(playerScore.getElixirScore() == 2);
	assert(playerScore.getTotalScore() == 18);
	assert(playerScore.getOwnedTerritories() == p1OwnedTerritories);
	assert(playerScore.getOwnedContinents() == p1OwnedContinents);
	assert(playerScore.getAbilities() == p1Abilities);

	gameStatsObserver.update();

	delete game;

	std::cout << "All test cases passed..." << std::endl;
}

void GameStatisticsTests::Test_Driver() {
	//Create a deck used for the driver demo
	Deck* deck = new Deck();
	Card* card1 = new Card("Ancient Woods", 0, 0, 1, 0, "buildCity", "", false, 0, 0, false, 0, 0, "");
	Card* card2 = new Card("Noble Knight", 0, 0, 0, 1, "destroyArmy", "", false, 0, 0, false, 0, 0, "");
	Card* card3 = new Card("Dire Dragon", 3, 0, 0, 1, "newArmy", "destroyArmy", true, 0, 0, true, 0, 0, "");
	Card* card4 = new Card("Ancient Tree Spirit", 4, 0, 0, 0, "newArmy", "", false, 0, 0, false, 3, 0, "");
	Card* card5 = new Card("Ancient Woods", 1, 0, 1, 0, "buildCity", "newArmy", true, 0, 1, false, 0, 0, "");
	Card* card6 = new Card("Noble Hills", 3, 0, 0, 0, "newArmy", "", false, 0, 0, false, 0, 0, "3NobleCards=4VP");
	
	deck->addCard(card6);
	deck->addCard(card5);
	deck->addCard(card4);
	deck->addCard(card3);
	deck->addCard(card2);
	deck->addCard(card1);

	Resources* rsc = new Resources();
	BidTieBreakerByLastName tieBreaker;
	BiddingFacility* bf = new BiddingFacility(tieBreaker);
	Map* map = MapLoader::parseMap(mapPath);
	std::vector<Player*> pl{
		new Player(playerName, bf), 
		new Player(altPlayerName, bf)
	};

	//Create the game and attach Observer
	Game* newGame = new Game(rsc, map, deck, pl);
	GameStatistics* gameStatsObserver = new GameStatistics(newGame); //The observer attach it self to the game

	newGame->runSetupPhase(2);
	newGame->runRoundsUntilEndGame();
	newGame->endGame();

	delete newGame;
}