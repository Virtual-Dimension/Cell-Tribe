#pragma once
#include "Entity.h"

class EntityLiving : public Entity {
public:
	EntityLiving();
	~EntityLiving();
	virtual int update() override final;
	virtual bool canBeAttacked() const override final;
	virtual int beAttacked(EntityLiving*, const LL&) override;
	virtual void heal(const LL&);
protected:
	int atp;
	virtual int behavior() = 0;
	virtual int move(const Point&) = 0;
	virtual int attack(EntityLiving*);
	virtual int interact1(Entity*);
}; 
