#pragma once
#include "Entity.h"

class EntityLiving : public Entity {
public:
	EntityLiving();
	~EntityLiving();
	virtual int run() override final;
	virtual void beAttacked(EntityLiving*, const LL&);
	virtual void heal(const LL&);
protected:
	int atp;
	virtual int behavior() = 0;
	virtual int move(const Point&) = 0;
	virtual int attack(EntityLiving*);
	virtual int propagate();
	virtual int forage();
}; 
