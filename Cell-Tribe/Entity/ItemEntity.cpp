#include "ItemEntity.h"

ItemEntity::ItemEntity() : item(0) {}

ItemEntity::ItemEntity(Item* pItem) : item(pItem) {}

ItemEntity::~ItemEntity() { delete item; }
