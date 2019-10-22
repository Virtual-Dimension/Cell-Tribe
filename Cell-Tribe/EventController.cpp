#include "EventController.h"
#include "MapController.h"
#include "Entity/EntityMobTribe.h"

EventController::EventController(MapController* mapcontroller) : mapController(mapcontroller), TribeUpdateCD(0) {}

EventController::~EventController() {}

void EventController::update() {
	if (TribeUpdateCD > 0) TribeUpdateCD -= mapController->getSecond();
	if (TribeUpdateCD <= 0) {
		for (size_t i = 0; i < mapController->count(); i++) {
			if (mapController->getList()[i]->isPlayer()) {
				EntityMobTribe* newEntityMobTribe = new EntityMobTribe(mapController->getList()[i]->getPoint() + Point(rand() % 2000 - 1000, rand() % 2000 - 1000));
				if (newEntityMobTribe->spawn(mapController) != OPERATOR_SUCCESS) {
					delete newEntityMobTribe;
				}
				else {
					printf("[EventController]making...{%.2lf, %.2lf}\n", newEntityMobTribe->getPoint().x, newEntityMobTribe->getPoint().y);
					TribeUpdateCD = 5;
				}
			}
		}
		
	}
	// write down your function
	return;
}

void EventController::close() { mapController->erase(this); }

void EventController::open() { mapController->push(this); }
