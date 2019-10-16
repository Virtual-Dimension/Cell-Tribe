#include "EntityLiving.h"

EntityLiving::EntityLiving() : Entity(), atp(1) {}

EntityLiving::~EntityLiving() {}

int EntityLiving::run() {
	if (health <= 0) death = 1;
	if (death) return TRIBE_DEAD;

	int bh_res = behavior();
	if (bh_res != OPERATOR_SUCCESS) return bh_res;

	// more_opt
	return OPERATOR_SUCCESS;
}

void EntityLiving::beAttacked(EntityLiving* other, const LL& damage) {
	health -= damage;
	if (health <= 0) death = 1;
	return;
}

void EntityLiving::heal(const LL& val) { health+= val;	return; }

int EntityLiving::forage() { return OPERATOR_SUCCESS; }

int EntityLiving::attack(EntityLiving* other) {
	other->beAttacked(this, atp);
	return OPERATOR_SUCCESS;
}

int EntityLiving::propagate() { return OPERATOR_SUCCESS; }
