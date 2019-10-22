#include "EntityEnergy.h"
#include "../MapController.h"

EntityEnergy::EntityEnergy(int energyNumMaxLim) : energyNum(0) {
	this->makeEnergy(energyNumMaxLim);
}

EntityEnergy::~EntityEnergy() {}

void EntityEnergy::makeEnergy(int energyNumMaxLim) {
	this->energyNum = rand() % energyNumMaxLim;
	if (energyNum <= energyNumMaxLim / 2) this->energyNum += energyNumMaxLim;
}

int EntityEnergy::getEnergyNum() { return energyNum; }

int EntityEnergy::beUsed(EntityLiving* entity) {
	if (entity->isPlayer()) {
		entity->energyUp(this->energyNum);
		this->setDeath();
		return OPERATOR_SUCCESS;
	}
	return OPERATOR_FAILED;
}