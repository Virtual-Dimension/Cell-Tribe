#include "EntityMobTribe.h"
#include "../MapController.h"

EntityMobTribe::EntityMobTribe() : EntityBaseTribe(), atkEntity(0), viewRange(0) {
	healthMax = 20;
	cellsMax = rand() % 30 + 10;
	cellRadius = 5;
	atk = 10;
	health = 5.0;
	moveRange = 100;
	moveSpeed = 10;
	viewRange = 500;
	propagate();
}

EntityMobTribe::~EntityMobTribe() {
}
int EntityMobTribe::behavior() {
	int baseRes = EntityBaseTribe::behavior();
	if (baseRes < 0) return baseRes;

	if (atkEntity && !getMapController()->exist(atkEntity)) atkEntity = 0;
	if (atkEntity && (atkEntity->getPoint() - getPoint()).len() > viewRange) atkEntity = 0;
	if (atkEntity) move(atkEntity->getPoint());

	/*if (slGetMouseButton(SL_MOUSE_BUTTON_RIGHT)) {
		propagate();
	}
	if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT)) {
		move(SL::GetRelativeMousePos());
	}
	if (slGetKey('1')) {
		status ^= STATUS_ATTACK;
		printf("ATTACKMODE : %d\n", status & STATUS_ATTACK);
	}
	if (slGetKey('2')) {
		status ^= STATUS_USE;
		printf("USEMODE : %d\n", status & STATUS_USE);
	}


	if (((SLDynamicPointGroup*)slObject)->IsStatic()) {
		SL::CameraMove(getPoint().x + SL::GetCameraOffset().x - WINDOW_WIDTH / 2, getPoint().y + SL::GetCameraOffset().y - WINDOW_HEIGHT / 2);
	}*/

	return OPERATOR_SUCCESS;
}

int EntityMobTribe::interact(Entity* entity) {
	if (entity->canBeAttacked()) {
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
