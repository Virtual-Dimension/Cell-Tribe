#pragma once
#include "../Item.h"

class ItemEntity: public BaseEntity{
protected:
	Item * item;
public:
	ItemEntity();
	ItemEntity(Item*);
	virtual ~ItemEntity();
};
