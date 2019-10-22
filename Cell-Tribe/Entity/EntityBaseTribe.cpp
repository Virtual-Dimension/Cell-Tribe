#include "EntityBaseTribe.h"
#include "../Graph/slr.h"
#include "../MapController.h"

EntityBaseTribe::EntityBaseTribe()
	: EntityLiving(), cellsMax(0), regeneration(0), cellRadius(0), moveCD(0), propagateCD(0), pointColor((double)(rand() % 256) / 256) {}

EntityBaseTribe::~EntityBaseTribe() {}

int EntityBaseTribe::move(const Point& p) {
	if (moveCD > 0) return ENTITY_MOVING;
	if (getMapController()->beyond(p) || (p - getPoint()).len() > moveRange)return ENTITY_MOVEOUT;
	((SLDynamicPointGroup*)slObject)->move(p);
	setPoint(p);
	moveCD = 2;
	return OPERATOR_SUCCESS;
}

int EntityBaseTribe::onSpawning(MapController* mapController) {
	SLDynamicPointGroup* newSLObject = new SLDynamicPointGroup();
	newSLObject->move_speed = moveSpeed, newSLObject->static_speed = 5.0;
	int siz = (int)cellsPoint.size();
	for (auto dypoint : cellsPoint)	delete dypoint.point;
	cellsPoint.clear();
	for (int i = 0; i < siz; i++) {
		SLColor newSLColor = HSL2RGB(std::max(std::min(1.0, pointColor + 0.2 * rand() / RAND_MAX - 0.1), 0.0), 1, 0.5, 0.3 + (double)rand() / RAND_MAX * 0.7);
		SLDynamicPoint* newSLDynamicPoint = new SLDynamicPoint(getPoint(), cellRadius, 10, newSLColor);
		cellsPoint.push_back(CellPoint{ newSLDynamicPoint, healthMax });
		newSLObject->AddPoint(newSLDynamicPoint);
	}
	newSLObject->move(getPoint());
	slObject = newSLObject;
	return OPERATOR_SUCCESS;
}

int EntityBaseTribe::beAttacked(EntityLiving* other) {
	for (std::list < CellPoint >::iterator it = cellsPoint.begin(); it != cellsPoint.end(); ) {
		it->health -= other->getAttackDamage(it->point->GetPos(), cellRadius);
		if (it->health <= 0) {
			((SLDynamicPointGroup*)slObject)->RemovePoint(it->point);
			it = cellsPoint.erase(it);
		}
		else {
			++it;
		}
	}
	if (cellsPoint.empty()) {
		setDeath();
	}
	return OPERATOR_SUCCESS;
}

double EntityBaseTribe::getAttackDamage(const Point& p, const double& r) {
	double res = 0;
	for (auto cell : cellsPoint) 
		if ((p - cell.point->GetPos()).len() < r + attackRange) res += atk * getMapController()->getSecond();
	return res;
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
	if (moveCD > 0) moveCD -= getMapController()->getSecond();
	if (propagateCD > 0) propagateCD -= getMapController()->getSecond();
	heal(regeneration * getMapController()->getSecond());
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
		if (it != cellsPoint.end()) newPoint = it->point->GetPos(), ++it;
		SLColor newSLColor = HSL2RGB(std::max(std::min(1.0, pointColor + 0.2 * rand() / RAND_MAX - 0.1), 0.0), 1, 0.5, 0.3 + (double)rand() / RAND_MAX * 0.7);
		SLDynamicPoint* newSLDynamicPoint = new SLDynamicPoint(newPoint, cellRadius, 10, newSLColor);
		cellsPoint.push_back(CellPoint{ newSLDynamicPoint, healthMax });
		if (slObject) ((SLDynamicPointGroup*)slObject)->AddPoint(newSLDynamicPoint);
	}
	if (slObject)((SLDynamicPointGroup*)slObject)->move(getPoint());
	propagateCD = 2;
	return OPERATOR_SUCCESS;
}

bool EntityBaseTribe::inRange(const Point& p, const double& r) const {
	for (auto dypoint : cellsPoint)
		if ((dypoint.point->GetPos() - p).len() < r + cellRadius) return 1;
	return 0;
}
