
#pragma region Header


#include "Item.h"
#include "ItemManager.h"
#include "MapController.h"
#include "./Entity/PlayerTribe.h"

#pragma endregion

BaseEntity* player1, * player2;
MapController* mapc;

int main() {
	player1 = new PlayerTribe();
	player2 = new PlayerTribe();
	mapc = new MapController();
	while (true) {
		int flag= 0;
		std::cout << "Player1:" << std::endl;
		if (player1->run() == TRIBE_DEAD || player2->run() == TRIBE_DEAD) {
			break;
		}
	}
	printf("player1 : %d, player2 : %d", player1->getDeath(), player2->getDeath());

	//PlayerTribe a;


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