#pragma once
#include "EntityItem.h"
#include "EntityLiving.h"

class EntityEnergy : public EntityItem {
public:
	EntityEnergy(int);
	~EntityEnergy();
	void makeEnergy(int);
	int getEnergyNum();
	int beUsed(EntityLiving* entity);
private:
	int energyNum;
};

