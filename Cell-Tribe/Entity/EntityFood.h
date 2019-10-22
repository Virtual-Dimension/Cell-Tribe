#pragma once
#include "EntityItem.h"
#include "EntityLiving.h"

class EntityFood : public EntityItem {
public:
	EntityFood(int);
	~EntityFood();
	void makeFood(int);
	int getFoodNum();
	int beUsed(EntityLiving* entity);
private:
	int foodNum;
};

