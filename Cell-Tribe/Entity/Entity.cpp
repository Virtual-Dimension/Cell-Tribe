#include "EntityLiving.h"
#include "../MapController.h"

Entity::Entity() : death(0), show(0), health(0), mapController(0), slObject(0), showObject(0), point() {}

Entity:: ~Entity() { }

void Entity::setDeath() { death = 1; }

void Entity::setPoint(const Point& p) { point = p; }

void Entity::setPoint(const double& x, const double& y) { setPoint(Point(x, y)); }

void Entity::setMapController(MapController* mapcontroller, const bool& x) {
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

void Entity::display(const bool& x) {
	if (showObject == x) return;
	if (showObject) {
		slObject->detach();
	}
	else {
		slObject->attach();
	}
	showObject ^= 1;
	return;
}

MapController* Entity::getMapController()const { return show ? mapController : nullptr; }

bool Entity::getDeath() const { return death; }

bool Entity::getDisplay() const { return showObject; }

double Entity::getHealth() const { return health; }

Point Entity::getPoint() const { return point; }

bool Entity::inRange(const Point& p) const { return inRange(p, 1); }

bool Entity::inRange(const Point& p, const double& dis) const { return (point - p).len() < dis; }

bool Entity::canBeAttacked() const { return false; }

int Entity::beAttacked(EntityLiving* other, const double& damage) { return OPERATOR_SUCCESS; }

bool Entity::canBeUsed() const { return false; }

int Entity::beUsed(EntityLiving* other) { return OPERATOR_SUCCESS; }

int Entity::respawn(MapController* mapcontroller) {
	point = mapcontroller->getRightPoint();
	return spawn(mapcontroller);
}

int Entity::spawn(MapController* mapcontroller) {
	setMapController(mapcontroller, 0);
	if (mapcontroller->beyond(point)) return ENTITY_BEYOND;
	setMapController(mapcontroller, 1);
	display(1);
	return OPERATOR_SUCCESS;
}

bool Entity::isPlayer() const { return false; }
