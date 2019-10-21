#include "EntityBaseTribe.h"
#include "../Graph/slr.h"
#include "../MapController.h"

EntityBaseTribe::EntityBaseTribe()
	: EntityLiving(), cellsMax(0), energyMax(0), energy(0), regeneration(0), cellRadius(0), moveCD(0), propagateCD(0) {}

EntityBaseTribe::~EntityBaseTribe() {}

int EntityBaseTribe::move(const Point& p) {
	if (moveCD > 0) return ENTITY_MOVING;
	if (getMapController()->beyond(p) || (p - getPoint()).len() > moveRange)return ENTITY_MOVEOUT;
	((SLDynamicPointGroup*)slObject)->move(p);
	setPoint(p);
	moveCD = 2;
	return OPERATOR_SUCCESS;
}

int EntityBaseTribe::spawn(MapController* mapController) {
	if (slObject) {
		slObject->detach();
		delete slObject;
	}
	SLDynamicPointGroup* newSLObject = new SLDynamicPointGroup();
	newSLObject->move_speed = moveSpeed, newSLObject->static_speed = 5.0;
	int siz = (int)cellsPoint.size();
	for (auto dypoint : cellsPoint)	delete dypoint.point;
	cellsPoint.clear();
	for (int i = 0; i < siz; i++) {
		SLDynamicPoint* newSLDynamicPoint = new SLDynamicPoint(getPoint(), cellRadius, 10, randSLColor());
		cellsPoint.push_back(CellPoint{ newSLDynamicPoint, healthMax });
		newSLObject->AddPoint(newSLDynamicPoint);
	}
	newSLObject->move(getPoint());
	slObject = newSLObject;
	return EntityLiving::spawn(mapController);
}

int EntityBaseTribe::beAttacked(EntityLiving*, const double&) {
	return 0;
}

void EntityBaseTribe::heal(const double& val) {
	for (auto dypoint : cellsPoint)	dypoint.health = std::min(healthMax, dypoint.health + val);
	return;
}

int EntityBaseTribe::behavior() {
	if (cellsPoint.size() == 0) {
		health = 0;
		return ENTITY_DEAD;
	}
	if (moveCD > 0) moveCD -= getMapController()->getStick();
	if (propagateCD > 0) propagateCD -= getMapController()->getStick();
	heal(regeneration * getMapController()->getStick());
	return OPERATOR_SUCCESS;
}

int EntityBaseTribe::propagate() {
	if (propagateCD > 0) return ENTITY_PROPAGATING;
	if (slObject && !((SLDynamicPointGroup*)slObject)->IsStatic()) return ENTITY_MOVING;
	int addval = std::min((int)cellsPoint.size() / 2 + 1, cellsMax - (int)cellsPoint.size());
	if (addval <= 0) return ENTITY_TOOMANY;
	Point newPoint = getPoint();
	std::list < CellPoint >::iterator it = cellsPoint.begin();
	for (int i = 0; i < addval; i++) {
		if (it != cellsPoint.end()) newPoint = it->point->GetPos();
		SLDynamicPoint* newSLDynamicPoint = new SLDynamicPoint(newPoint, cellRadius, 10, randSLColor());
		cellsPoint.push_back(CellPoint{ newSLDynamicPoint, healthMax });
		if (slObject) ((SLDynamicPointGroup*)slObject)->AddPoint(newSLDynamicPoint);
	}
	if (slObject)((SLDynamicPointGroup*)slObject)->move(getPoint());
	propagateCD = 2;
	return OPERATOR_SUCCESS;
}
int EntityBaseTribe::attack(EntityLiving* other) {
	// calc
	return OPERATOR_SUCCESS;
}

bool EntityBaseTribe::inRange(const Point& p, const double& dis) const {
	for (auto dypoint : cellsPoint)
		if ((dypoint.point->GetPos() - p).len() < dis) return 1;
	return 0;
}
