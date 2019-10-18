#include "EntityEnergy.h"
#include "../MapController.h"

EntityEnergy::EntityEnergy() : EnergyNum(0) {}

EntityEnergy::~EntityEnergy() {}

void EntityEnergy::MakeEnergy(MapController* mapcontroller, int EnergyNumMaxLim)
{
	Point EnergyPoint = mapcontroller->getRightPoint();
	this->EnergyNum = rand() % EnergyNumMaxLim;
	if (EnergyNum <= EnergyNumMaxLim / 2) this->EnergyNum += EnergyNumMaxLim;
	this->setPoint(EnergyPoint);
	mapcontroller->push(this);
}

