#pragma once
#include "Entity.h"

class EntityItem: public Entity{
public:
	EntityItem();
	virtual ~EntityItem();
	virtual void beUsed(EntityLiving*);
protected:
	//

};
