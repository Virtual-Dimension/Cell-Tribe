
#pragma region Header

#include "EventController.h"
#include "EvolutionController.h"
#include "MapController.h"
#include "Entity/EntityPlayerTribe.h"
#include <Windows.h>
#pragma endregion




void InitGame() {
	Entity* player1;

	EvolutionController* evolutionController1 = new EvolutionController("evolution.json");

	player1 = new EntityPlayerTribe("Player1", evolutionController1);

	MapController* mapController = new MapController(MAP_BEGIN_X, MAP_BEGIN_Y, MAP_END_X, MAP_END_Y);

	player1->respawn(mapController);

	EventController* eventController = new EventController(mapController);

	eventController->open();

	SL::CameraMove(player1->getPoint().x - WINDOW_WIDTH / 2, player1->getPoint().y - WINDOW_HEIGHT / 2);

	//SL::CameraMove(100, 100);
	return;
}

int main() {
	srand((int)time(0));

	printf("starting window...\n");

	SL::StartThread(WINDOW_WIDTH, WINDOW_HEIGHT);

	while (!SL::IsWindowShowed()) Sleep(1);

	printf("init game...\n");

	InitGame();

	printf("start game...\n");

	SL::Wait();

	return 0;
}