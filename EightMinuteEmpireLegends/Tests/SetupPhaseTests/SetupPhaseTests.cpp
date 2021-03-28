#include "SetupPhaseTests.h"


#include "../../Core/GameCore/GameCore.h"
#include "../../Core/MapLoader/MapLoader.h"


void SetupPhaseTests::Test_SetupPhaseAndGameLoopExecutes_GivenValidInput()
{
	std::vector<std::string> names{ "Coucou", "Banane" };
	std::string mapPath = "..\\Tests\\SetupPhaseTests\\Resources\\narrows.json";
	Game* validGame = GameBuilder::build(2, names, mapPath);
	validGame->runSetupPhase();
	validGame->runRoundsUntilEndGame();
}
