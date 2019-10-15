#include "Item.h"

Item::Item() {}

Item::~Item(){}

int Item::onPickedup(BaseEntity* tribe) { return OPERATOR_SUCCESS; }

int Item::onUsing(BaseEntity* tribe) { return OPERATOR_SUCCESS; }

int Item::onDropped(BaseEntity* tribe) { return OPERATOR_SUCCESS; }


