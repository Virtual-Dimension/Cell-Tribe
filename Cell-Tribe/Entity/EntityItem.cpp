#include "EntityItem.h"

EntityItem::EntityItem() {}

int EntityItem::update() {
	// print
	return 0;
}

EntityItem::~EntityItem() {}

bool EntityItem::canBeUsed() const { return true; }

int EntityItem::beUsed(EntityLiving*) {
	// I think we should do something to living entity
	return OPERATOR_SUCCESS;
}
