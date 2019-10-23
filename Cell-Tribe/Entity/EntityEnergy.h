#pragma once
#include "EntityItem.h"

class EntityLiving;

class EntityEnergy : public EntityItem {
public:
	EntityEnergy(int);
	~EntityEnergy();
	virtual int onSpawning(MapController*) override;
	virtual int beUsed(EntityLiving* entity) override;
private:
	int energyNum;
};

