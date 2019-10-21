#pragma once
#include "Entity.h"

class EntityItem: public Entity{
public:
	EntityItem();
	virtual ~EntityItem();

	virtual int update() override final;
	virtual bool canBeUsed() const override final;
	virtual int beUsed(EntityLiving*) override;

};
