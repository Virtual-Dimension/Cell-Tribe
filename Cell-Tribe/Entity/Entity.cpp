#include "Entity.h"
#include "EntityLiving.h"

Entity::Entity() : death(0), show(0), health(0), mapController(0) {}

Entity:: ~Entity() { if (show) mapController->erase(this); }

void Entity::setDeath() { death = 1; }

void Entity::setPoint(const Point& p) { point = p; }

void Entity::setPoint(const double& x, const double& y) { setPoint(Point(x, y)); }

void Entity::setShow(MapController* mapcontroller, const bool& x) {
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

MapController* Entity::getMapController() { return show ? mapController : nullptr; }

bool Entity::getDeath() const { return death; }

double Entity::getHealth() const { return health; }

Point Entity::getPoint() const { return point; }

int Entity::inRange(const Point& p) const { return inRange(p, 1); }

int Entity::inRange(const Point& p, const double& dis) const { return (point - p).len() < dis; }



bool Entity::canBeAttacked() const { return false; }

int Entity::beAttacked(EntityLiving* other, const double& damage) { return OPERATOR_SUCCESS; }

bool Entity::canBeUsed() const { return false; }

int Entity::beUsed(EntityLiving* other) { return OPERATOR_SUCCESS; }

int Entity::respawn(MapController* mapcontroller) {
	setShow(mapcontroller, 0);
	point = mapcontroller->getRightPoint();
	setShow(mapcontroller, 1);
	return OPERATOR_SUCCESS;
}
