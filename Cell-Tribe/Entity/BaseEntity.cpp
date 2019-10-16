#include "BaseEntity.h"

BaseEntity::BaseEntity() : death(0), show(0), mapController(0) {}

BaseEntity:: ~BaseEntity() { if (show) mapController->erase(this); }

void BaseEntity::setDeath() { death = 1; }

void BaseEntity::setPoint(const Point& p) { point = p; }

void BaseEntity::setShow(MapController* mapcontroller, const bool& x) {
	if (show == x) return;
	if (show) {
		mapController->erase(this);
		mapController = 0;
	}
	else {
		mapController = mapcontroller;
		mapController->push(this);
	}
	show ^= 1;
	return;
}
MapController* BaseEntity::getMapController() { return show ? mapController : nullptr; }

int BaseEntity::getDeath() const { return death; }

Point BaseEntity::getPoint() const { return point; }

int BaseEntity::inRange(const Point& p) const { return abs(point.x - p.x) < 1 && abs(point.y - p.y) < 1; }
