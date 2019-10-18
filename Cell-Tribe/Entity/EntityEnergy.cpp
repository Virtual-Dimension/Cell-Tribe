#include "EntityEnergy.h"
#include <cstdlib>
#include <ctime>

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

