#include "EntityMobTribe.h"
#include "../MapController.h"

EntityMobTribe::EntityMobTribe() : EntityBaseTribe(), atkEntity(0), viewRange(0) {
	healthMax = 20;
	cellsMax = rand() % 30 + 10;
	cellRadius = 5;
	atk = 10;
	health = 5.0;
	moveRange = 200 + (double)(rand() % 200);
	moveSpeed = 50 + (double)(rand() % 50);
	viewRange = 500;
	attackRange = 100;
	propagate();
}

EntityMobTribe::EntityMobTribe(const Point& p) : EntityBaseTribe(), atkEntity(0), viewRange(0) {
	healthMax = 20;
	cellsMax = rand() % 30 + 10;
	cellRadius = 5;
	atk = 10;
	health = 5.0;
	moveRange = 200 + (double)(rand() % 200);
	moveSpeed = 50 + (double)(rand() % 50);
	viewRange = 500;
	attackRange = 100;
	propagate();
	setPoint(p);
}

EntityMobTribe::~EntityMobTribe() {
}
int EntityMobTribe::behavior() {
	int baseRes = EntityBaseTribe::behavior();
	if (baseRes < 0) return baseRes;
	if (atkEntity && !getMapController()->exist(atkEntity)) atkEntity = 0;
	if (atkEntity && (atkEntity->getPoint() - getPoint()).len() > viewRange) atkEntity = 0;
	if (atkEntity) move(atkEntity->getPoint());
	if (!atkEntity) {
		if (rand() % 2)	move(getMapController()->getRightPoint());
		else propagate();
	}

	return OPERATOR_SUCCESS;
}

int EntityMobTribe::beAttacked(EntityLiving* entity) {
	if (!atkEntity) atkEntity = entity;
	return EntityBaseTribe::beAttacked(entity);
}

int EntityMobTribe::interact(Entity* entity) {
	if (!atkEntity && entity->isPlayer() && (entity->getPoint() - getPoint()).len() < viewRange) atkEntity = entity;
	if (atkEntity && atkEntity == entity) {
		for (auto cell : cellsPoint) {
			if (entity->inRange(cell.point->GetPos(), attackRange)) {
				attack((EntityLiving*)entity);
				return ENTITY_ATTACKED;
			}
		}
	}
	return OPERATOR_SUCCESS;
}

int EntityMobTribe::move(const Point& p) {
	if (EntityBaseTribe::move(p) == ENTITY_MOVEOUT) {
		if (getMapController()->beyond(p)) return ENTITY_MOVEOUT;
		Point nxtp = (p - getPoint()) / (p - getPoint()).len() * (moveRange - 0.1);
		return EntityBaseTribe::move(nxtp);
	}
	return OPERATOR_SUCCESS;
}
