#include "BaseEntity.h"

void BaseEntity::setDeath() { death = 1; }

void BaseEntity::setPoint() { death = 1; }

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
BaseEntity::BaseEntity() : death(0), show(0), mapController(0) {}

BaseEntity:: ~BaseEntity() {
	if (show) mapController->erase(this);
}

int BaseEntity::getDeath() const { return death; }

Point BaseEntity::getPoint() const { return point; }

int BaseEntity::inRange(const Point& p) const { return abs(point.x - p.x) < 1 && abs(point.y - p.y) < 1; }
