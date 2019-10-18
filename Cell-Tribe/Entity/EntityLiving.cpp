#include "EntityLiving.h"

EntityLiving::EntityLiving() : Entity(), atk(1), healthMax(20), attackRange(3), moveRange(3), moveSpeed(1) {}

EntityLiving::~EntityLiving() {}

int EntityLiving::update() {
	if (health <= 0) setDeath();
	if (getDeath()) return ENTITY_DEAD;

	int bh_res = behavior();
	if (bh_res != OPERATOR_SUCCESS) return bh_res;

	// more_opt
	return OPERATOR_SUCCESS;
}

int EntityLiving::print() const { return 0; }

bool EntityLiving::canBeAttacked() const { return true; }

int EntityLiving::beAttacked(EntityLiving* other, const double& damage) {
	health -= damage;
	if (health <= 0) setDeath();
	return OPERATOR_SUCCESS;
}

void EntityLiving::heal(const LL& val) { health = std::min(healthMax, health + val); }

int EntityLiving::attack(EntityLiving* other) {
	other->beAttacked(this, atk);
	return OPERATOR_SUCCESS;
}

int EntityLiving::move(const Point& p) {
	// API
	return OPERATOR_SUCCESS;
}

int EntityLiving::interact1(Entity* entity) {
	if (entity->canBeAttacked()) {
		this->attack((EntityLiving*)entity);
		return ENTITY_ATTACKED;
	}
	return OPERATOR_SUCCESS;
}