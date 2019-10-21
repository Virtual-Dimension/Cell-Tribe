#include "EntityLiving.h"

EntityLiving::EntityLiving() : Entity(), atk(0), healthMax(0), attackRange(0), moveRange(0), moveSpeed(0) {}

EntityLiving::~EntityLiving() {}

int EntityLiving::update() {
	if (health <= 0) setDeath();
	if (getDeath()) return ENTITY_DEAD;

	int bh_res = behavior();
	if (bh_res != OPERATOR_SUCCESS) return bh_res;

	// more_opt
	return OPERATOR_SUCCESS;
}

bool EntityLiving::canBeAttacked() const { return true; }

int EntityLiving::beAttacked(EntityLiving* other) {
	health -= other->getAttackDamage(getPoint(), getRadius());
	if (health <= 0) setDeath();
	return OPERATOR_SUCCESS;
}

double EntityLiving::getAttackDamage(const Point& p, const double& radius) { return atk; }

void EntityLiving::heal(const double& val) { health = std::min(healthMax, health + val); }

int EntityLiving::attack(EntityLiving* other) {
	other->beAttacked(this);
	return OPERATOR_SUCCESS;
}

int EntityLiving::move(const Point& p) {
	// API
	return OPERATOR_SUCCESS;
}
