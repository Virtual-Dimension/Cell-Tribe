#include "EntityLiving.h"

EntityLiving::EntityLiving() : Entity(), atp(1) {}

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

int EntityLiving::beAttacked(EntityLiving* other, const LL& damage) {
	health -= damage;
	if (health <= 0) setDeath();
	return OPERATOR_SUCCESS;
}

void EntityLiving::heal(const LL& val) { health+= val;	return; }

int EntityLiving::attack(EntityLiving* other) {
	other->beAttacked(this, atp);
	return OPERATOR_SUCCESS;
}

int EntityLiving::interact1(Entity* entity) {
	if (entity->canBeAttacked()) {
		this->attack((EntityLiving * )entity);
		return ITEM_USED;
	}
	return 0;
}