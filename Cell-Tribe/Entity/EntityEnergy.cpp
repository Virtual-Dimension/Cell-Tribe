#include "EntityEnergy.h"
#include "EntityLiving.h"
#include "../MapController.h"

EntityEnergy::EntityEnergy(int energyNumMaxLim) : energyNum(0) {
	this->energyNum = rand() % energyNumMaxLim;
	if (energyNum <= energyNumMaxLim / 2) this->energyNum += energyNumMaxLim;
	setRadius(5);
}

EntityEnergy::~EntityEnergy() {}

int EntityEnergy::onSpawning(MapController* mapController) {
	slObject = new SLDynamicPoint(getPoint(), getRadius(), 5, SLColor(0.9, 0.9, 0.9, 1));
	return OPERATOR_SUCCESS;
}

int EntityEnergy::beUsed(EntityLiving* entity) {
	if (entity->isPlayer()) {
		entity->energyUp(this->energyNum);
		this->setDeath();
		return OPERATOR_SUCCESS;
	}
	return OPERATOR_FAILED;
}