#pragma once
#include "EntityItem.h"

class EntityEnergy : public EntityItem {
public:
	EntityEnergy();
	~EntityEnergy();
	void MakeEnergy(MapController*, int);
private:
	int EnergyNum;
};

