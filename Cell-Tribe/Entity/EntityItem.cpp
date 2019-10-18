#include "EntityItem.h"

EntityItem::EntityItem() {}

int EntityItem::update() {
	return OPERATOR_SUCCESS;
}

int EntityItem::print() const{
	// API
	return OPERATOR_SUCCESS;
}

EntityItem::~EntityItem() {}

bool EntityItem::canBeUsed() const { return true; }

int EntityItem::beUsed(EntityLiving* entity) {
	// I think we should do something to living entity
	return OPERATOR_SUCCESS;
}
