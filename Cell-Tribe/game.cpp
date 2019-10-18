
#pragma region Header

#include "EventController.h"
#include "EvolutionController.h"
#include "MapController.h"
#include "Entity/EntityPlayerTribe.h"

#pragma endregion


int main() {
	//SL::StartThread(WINDOW_WIDTH, WINDOW_HEIGHT);

	Entity* player1, * player2;
	MapController* mapController;
	EventController* eventController;
	EvolutionController* evolutionController1;
	EvolutionController* evolutionController2;
	evolutionController1= new EvolutionController("evolution.json");
	evolutionController2= new EvolutionController("evolution.json");

	
	player1 = new EntityPlayerTribe("Player1", evolutionController1);
	player2 = new EntityPlayerTribe("Player2", evolutionController2);


	mapController = new MapController(MAP_BEGIN_X, MAP_BEGIN_Y, MAP_END_X, MAP_END_Y);

	player1->respawn(mapController);
	player2->respawn(mapController);

	eventController = new EventController(mapController);

	while (true) {
		mapController->update();
		eventController->update();
	}
	printf("player1 : %d, player2 : %d", player1->getDeath(), player2->getDeath());

	//EntityPlayerTribe a;


	return 0;
}

/*
控制单位：种群
	----个体：胞体
	----属性：
		----个数
		----强度（单个个体）
		----能量
	----显示：粒子效果
	----行为：
		----移动
		----攻击
		----觅食，吞噬
			----获取能量，基因点数
		----繁殖：
			----消耗能量，增加个体数量
			----概率突变：
				----有利变异：
				----不利变异：消耗基因点数退化
	----进化：
		----消耗基因点数进行进化
地图：
	----显示各种群
	----一些物品
		----食物

*/