#include "EntityFood.h"
#include "../MapController.h"

EntityFood::EntityFood(int foodNumMaxLim) : foodNum(0) {
	this->makeFood(foodNumMaxLim);
}

EntityFood::~EntityFood() {}

void EntityFood::makeFood(int foodNumMaxLim) {
	this->foodNum = rand() % foodNumMaxLim;
	if (foodNum <= foodNumMaxLim / 2) this->foodNum += foodNumMaxLim;
}

int EntityFood::getFoodNum()
{
	return this->foodNum;
}

int EntityFood::beUsed(EntityLiving* entity)
{
	if (entity->isPlayer()) {
		entity->heal(this->foodNum);
		this->setDeath();
		return OPERATOR_SUCCESS;
	}
	return OPERATOR_FAILED;
}