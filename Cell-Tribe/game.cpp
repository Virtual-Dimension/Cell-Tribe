
#pragma region Header

#include "EventController.h"
#include "EvolutionController.h"
#include "MapController.h"
#include "Entity/EntityPlayerTribe.h"
#include <Windows.h>
#pragma endregion

MapController* mapController;

EventController* eventController;

void InitGame() {
	Entity* player1;

	EvolutionController* evolutionController1 = new EvolutionController("evolution.json");

	player1 = new EntityPlayerTribe("Player1", evolutionController1);

	mapController = new MapController(MAP_BEGIN_X, MAP_BEGIN_Y, MAP_END_X, MAP_END_Y);

	player1->spawn(mapController);

	eventController = new EventController(mapController);

	//SL::CameraMove(player1->getPoint().x, player1->getPoint().y);

	return;
}

int main() {
	srand((int)time(0));

	InitGame();

	SL::StartThread(WINDOW_WIDTH, WINDOW_HEIGHT);

	while (!SL::IsWindowShowed()) Sleep(1);

	//EntityPlayerTribe a;
	SL::Wait();

	return 0;
}

/*
���Ƶ�λ����Ⱥ
	----���壺����
	----���ԣ�
		----����
		----ǿ�ȣ��������壩
		----����
	----��ʾ������Ч��
	----��Ϊ��
		----�ƶ�
		----����
		----��ʳ������
			----��ȡ�������������
		----��ֳ��
			----�������������Ӹ�������
			----����ͻ�䣺
				----�������죺
				----�������죺���Ļ�������˻�
	----������
		----���Ļ���������н���
��ͼ��
	----��ʾ����Ⱥ
	----һЩ��Ʒ
		----ʳ��

*/