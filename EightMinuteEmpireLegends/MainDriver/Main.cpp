#include <iostream>
#include <string>
#include <algorithm>    // std::random_shuffle
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand

#include "../Map/DriverUtils.h"
#include "../Map/Map.h"
#include "../MapLoader/MapLoader.h"
#include "../Player/Player.h"
#include "../Cards/Cards.h"
#include "../BiddingFacility/BiddingFacility.h"
#include "../BiddingFacility/BidTieBreakerByLastName.h"

int runMapDriver() {

	// Valid map example	

	Continent* c1 = new Continent();
	c1->name = "Europe";
	Continent* c2 = new Continent();
	c2->name = "Asia";
	Continent* c3 = new Continent();
	c3->name = "Africa";
	Continent* c4 = new Continent();
	c4->name = "Oceania";

	Territory* t1 = new Territory("France", c1->name);
	Territory* t2 = new Territory("Germany", c1->name);
	Territory* t3 = new Territory("Egypt", c3->name);
	Territory* t4 = new Territory("Uganda", c3->name);
	Territory* t5 = new Territory("China", c2->name);
	Territory* t6 = new Territory("New Zealand", c4->name);

	Vertex* v1 = new Vertex(t1, "u");
	Vertex* v2 = new Vertex(t2, "v");
	Vertex* v3 = new Vertex(t3, "w");
	Vertex* v4 = new Vertex(t4, "x");
	Vertex* v5 = new Vertex(t5, "y");
	Vertex* v6 = new Vertex(t6, "z");

	Edge* e1 = new Edge(v1, v2, "a");
	Edge* e2 = new Edge(v1, v3, "b");
	Edge* e3 = new Edge(v3, v4, "c");
	Edge* e4 = new Edge(v2, v4, "d");
	Edge* e5 = new Edge(v1, v4, "e");
	Edge* e6 = new Edge(v2, v3, "f");
	Edge* e7 = new Edge(v2, v5, "g");
	Edge* e8 = new Edge(v4, v5, "h");
	Edge* e9 = new Edge(v5, v6, "i");

	Map* m1 = new Map("Earth", { c1, c2, c3, c4 });

	m1->insertVertex(v1);
	m1->insertVertex(v2);
	m1->insertVertex(v3);
	m1->insertVertex(v4);
	m1->insertVertex(v5);
	m1->insertVertex(v6);

	m1->insertEdge(e1);
	m1->insertEdge(e2);
	m1->insertEdge(e3);
	m1->insertEdge(e4);
	m1->insertEdge(e5);
	m1->insertEdge(e6);
	m1->insertEdge(e7);
	m1->insertEdge(e8);
	m1->insertEdge(e9);

	std::cout << "Validating Map 1 - " << (m1->validate() ? "Valid" : "Invalid") << std::endl;

	// Invalid map example	

	Continent* cc1 = new Continent();
	cc1->name = "Europe";
	Continent* cc2 = new Continent();
	cc2->name = "Asia";
	Continent* cc3 = new Continent();
	cc3->name = "Africa";
	Continent* cc4 = new Continent();
	cc4->name = "Oceania";

	Territory* tt1 = new Territory("France", cc1->name);
	Territory* tt2 = new Territory("Germany", cc1->name);
	Territory* tt3 = new Territory("Egypt", cc3->name);
	Territory* tt4 = new Territory("Uganda", cc3->name);
	Territory* tt5 = new Territory("China", cc2->name);
	Territory* tt6 = new Territory("New Zealand", cc4->name);

	Vertex* vv1 = new Vertex(tt1, "u");
	Vertex* vv2 = new Vertex(tt2, "v");
	Vertex* vv3 = new Vertex(tt3, "w");
	Vertex* vv4 = new Vertex(tt4, "x");
	Vertex* vv5 = new Vertex(tt5, "y");
	Vertex* vv6 = new Vertex(tt6, "z");

	Edge* ee1 = new Edge(v1, v2, "a");
	Edge* ee2 = new Edge(v1, v3, "b");
	Edge* ee3 = new Edge(v3, v4, "c");
	Edge* ee4 = new Edge(v2, v4, "d");
	Edge* ee5 = new Edge(v1, v4, "e");
	Edge* ee6 = new Edge(v2, v3, "f");
	Edge* ee9 = new Edge(v5, v6, "i");

	Map* m2 = new Map("Earth", { cc1, cc2, cc3, cc4 });

	m2->insertVertex(vv1);
	m2->insertVertex(vv2);
	m2->insertVertex(vv3);
	m2->insertVertex(vv4);
	m2->insertVertex(vv5);
	m2->insertVertex(vv6);

	// Notice that we are not inserting edge e7 and e8 in our graph, which means vectors v5 and v6 will be disconnected
	m2->insertEdge(ee1);
	m2->insertEdge(ee2);
	m2->insertEdge(ee3);
	m2->insertEdge(ee4);
	m2->insertEdge(ee5);
	m2->insertEdge(ee6);
	m2->insertEdge(ee9);

	std::cout << "Validating Map 2 - " << (m2->validate() ? "Valid" : "Invalid") << std::endl << std::endl;

	// Graph information on Map 1
	std::cout << "Map 1 " << vertices_toString(m1->vertices()) << std::endl;
	std::cout << "Map 1 " << edges_toString(m1->edges()) << std::endl;
	std::cout << "Map 1 " << continents_toString(m1->continents()) << std::endl;
	std::cout << "Map 1 " << territories_toString(m1->vertices()) << std::endl;
	std::cout << "Map 1 " << continents_toString(m1) << std::endl << std::endl;

	// Graph information on Map 2
	std::cout << "Map 2 " << vertices_toString(m2->vertices()) << std::endl;
	std::cout << "Map 2 " << edges_toString(m2->edges()) << std::endl;
	std::cout << "Map 2 " << continents_toString(m2->continents()) << std::endl;
	std::cout << "Map 2 " << territories_toString(m2->vertices()) << std::endl;
	std::cout << "Map 2 " << continents_toString(m2) << std::endl;

	delete m1;
	delete m2;

	return 0;
}

int runMapLoaderDriver() {
	//The file is stored in \eight-minute-empire-legends\EightMinuteEmpireLegends\Debug, make sure you have the map1.json file there
	std::cout << "Load a valid map file..." << std::endl;
	Map* map1 = MapLoader::parseMap("./Resources/validJson_validMap_simple.json");
	delete map1;

	std::cout << "\nLoad a valid map file..." << std::endl;
	Map* map2 = MapLoader::parseMap("./Resources/validJson_validMap.json");
	delete map2;

	std::cout << "\nLoad a incorrect file format (CSV)..." << std::endl;
	Map* map3 = MapLoader::parseMap("./Resources/wrongFormatFile.csv"); //Pointer will be null

	std::cout << "\nLoad a json file, but with missing continents data..." << std::endl;
	Map* map4 = MapLoader::parseMap("./Resources/invalidJson_missingContinents.json");

	std::cout << "\nLoad a json file, but with missing vertices..." << std::endl;
	Map* map5 = MapLoader::parseMap("./Resources/invalidJson_missingVertices.json");

	std::cout << "\nLoad a json file, but with wrong data type..." << std::endl;
	Map* map6 = MapLoader::parseMap("./Resources/invalidJson_wrongDataType.json");

	std::cout << "\nLoad a json file, but it is a disconnected graph..." << std::endl;
	Map* map7 = MapLoader::parseMap("./Resources/validJson_invalidMap.json");

	return 0;
}

int runCardsDriver() {
	std::cout << "This is the cards driver!" << std::endl;

	// Assuming there are 3 players
	int numPlayer = 3;
	std::cout << "Assuming a 3 players game" << std::endl;

	//Deck reveal() is included to demo deck functionality, NOT included in actual game
	//Demo deck
	Deck testDeck(numPlayer);
	testDeck.reveal();

	//Demo hand
	Hand testHand(testDeck);

	//Demo exchange cards until both Deck and Hand are emptry
	while (testHand.getSize() > 0) {
		testHand.exchange(testDeck, true); //Invoked demo mode here to automate all user interaction
		testDeck.reveal();
	}
	std::cout << "Hand has been depleted, demo ends" << std::endl;

	return 0;
}

int runBiddingFacilityDriver() {
	BidTieBreakerByLastName tieBreaker;

	/////////////////////////////////////////
	// Test player with most coins wins

	BiddingFacility t1_biddingFacility(tieBreaker);

	BidSubmission t1_bidPlayerA(
		"playerA",
		"aalfredson",
		0
	);
	BidSubmission t1_bidPlayerB(
		"playerB",
		"balfredson",
		3
	);
	BidSubmission t1_bidPlayerC(
		"playerC",
		"calfredson",
		2
	);

	t1_biddingFacility.trySubmitBid(t1_bidPlayerA);
	t1_biddingFacility.trySubmitBid(t1_bidPlayerB);
	t1_biddingFacility.trySubmitBid(t1_bidPlayerC);

	// Assert
	if (t1_biddingFacility.getWinningBid().getPlayerID() != t1_bidPlayerB.getPlayerID())
		return 1;


	/////////////////////////////////////////
	// Test player alphabetically first last 
	// name wins when bids are tied

	BiddingFacility t2_biddingFacility(tieBreaker);

	BidSubmission t2_bidPlayerA(
		"playerA",
		"aalfredson",
		0
	);
	BidSubmission t2_bidPlayerB(
		"playerB",
		"balfredson",
		3
	);
	BidSubmission t2_bidPlayerC(
		"playerC",
		"calfredson",
		3
	);

	t2_biddingFacility.trySubmitBid(t2_bidPlayerA);
	t2_biddingFacility.trySubmitBid(t2_bidPlayerB);
	t2_biddingFacility.trySubmitBid(t2_bidPlayerC);

	// Assert
	if (t2_biddingFacility.getWinningBid().getPlayerID() != t2_bidPlayerB.getPlayerID())
		return 1;



	/////////////////////////////////////////
	// Test player alphabetically first last 
	// name wins when bids are zero

	BiddingFacility t3_biddingFacility(tieBreaker);

	BidSubmission t3_bidPlayerA(
		"playerA",
		"aalfredson",
		0
	);
	BidSubmission t3_bidPlayerB(
		"playerB",
		"balfredson",
		0
	);
	BidSubmission t3_bidPlayerC(
		"playerC",
		"calfredson",
		0
	);

	t3_biddingFacility.trySubmitBid(t3_bidPlayerA);
	t3_biddingFacility.trySubmitBid(t3_bidPlayerB);
	t3_biddingFacility.trySubmitBid(t3_bidPlayerC);

	// Assert
	if (t3_biddingFacility.getWinningBid().getPlayerID() != t3_bidPlayerA.getPlayerID())
		return 1;


	return 0;
}

int main(int argc, char** argv) {
	std::cout << "(1) Running the Map Driver..." << std::endl;
	runMapDriver();
	std::cout << "\n(2) Running the Map Loader Driver..." << std::endl;
	runMapLoaderDriver();
	std::cout << "\n(4) Running the Card Driver..." << std::endl;
	runCardsDriver();
	std::cout << "\n(5) Running the Bidding Facility Driver (the driver uses assertions so there will be no output)..." << std::endl;
	runBiddingFacilityDriver();
}



void runPlayerDriver() {
    Deck deck(2);
    BidTieBreakerByLastName bidTieBreakerByLastName;
    Player* p1 = new Player("player1", deck, bidTieBreakerByLastName);

    p1->BuildCity();
    p1->DestroyArmy();
    p1->MoveArmies();
    p1->MoveOverLand();
    p1->payCoin();
    p1->PlaceNewArmies();

    delete p1;
}

int main() {
    BidTieBreakerByLastName tieBreaker;

    runPlayerDriver();
    /////////////////////////////////////////
    // Test player with most coins wins

    BiddingFacility t1_biddingFacility(tieBreaker);

    BidSubmission t1_bidPlayerA(
        "playerA",
        "aalfredson",
        0
    );
    BidSubmission t1_bidPlayerB(
        "playerB",
        "balfredson",
        3
    );
    BidSubmission t1_bidPlayerC(
        "playerC",
        "calfredson",
        2
    );

    t1_biddingFacility.trySubmitBid(t1_bidPlayerA);
    t1_biddingFacility.trySubmitBid(t1_bidPlayerB);
    t1_biddingFacility.trySubmitBid(t1_bidPlayerC);

    // Assert
    if (t1_biddingFacility.getWinningBid().getPlayerID() != t1_bidPlayerB.getPlayerID())
        return 1;

    std::cout << "Hello World!";
    return 0;
}
