#include "EventController.h"
#include "MapController.h"

EventController::EventController(MapController* mapcontroller) : mapController(mapcontroller) {}

EventController::~EventController() {}

void EventController::update() {
	// write down your function
	return;
}

void EventController::close() { mapController->erase(this); }

void EventController::open() { mapController->push(this); }
