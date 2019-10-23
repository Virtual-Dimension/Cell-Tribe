#include "EventController.h"
#include "MapController.h"
#include "Entity/EntityMobTribe.h"
#include "Entity/EntityEnergy.h"

EventController::EventController(MapController* mapcontroller) : mapController(mapcontroller), TribeUpdateCD(0), EnergyUpdateCD(0) {}

EventController::~EventController() {}

void EventController::update() {
	if (TribeUpdateCD > 0) TribeUpdateCD -= mapController->getSecond();
	if (EnergyUpdateCD > 0) EnergyUpdateCD -= mapController->getSecond();
	if (TribeUpdateCD <= 0) {
		for (size_t i = 0; i < mapController->count(); i++) {
			if (mapController->getList()[i]->isPlayer()) {
				EntityMobTribe* newEntityMobTribe = new EntityMobTribe(mapController->getList()[i]->getPoint() + Point(rand() % 2000 - 1000, rand() % 2000 - 1000));
				if (newEntityMobTribe->spawn(mapController) != OPERATOR_SUCCESS) {
					delete newEntityMobTribe;
				}
				else {
					printf("[EventController]making mob...{%.2lf, %.2lf}\n", newEntityMobTribe->getPoint().x, newEntityMobTribe->getPoint().y);
					TribeUpdateCD = 5;
				}
			}
		}
	}
	if (EnergyUpdateCD <= 0) {
		EntityEnergy *newEntityEnergy = new EntityEnergy(100);
		if (newEntityEnergy->respawn(mapController) != OPERATOR_SUCCESS) {
			delete newEntityEnergy;
		}
		else {
			printf("[EventController]making energy...{%.2lf, %.2lf}\n", newEntityEnergy->getPoint().x, newEntityEnergy->getPoint().y);
			EnergyUpdateCD = 0.05;
		}
	}
	// write down your function
	return;
}

void EventController::close() { mapController->erase(this); }

void EventController::open() { mapController->push(this); }
