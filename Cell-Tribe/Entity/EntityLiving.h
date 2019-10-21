#pragma once
#include "Entity.h"

class EntityLiving : public Entity {
public:
	EntityLiving();
	~EntityLiving();
	virtual int update() override final;
	virtual bool canBeAttacked() const override final;
	virtual int beAttacked(EntityLiving*, const double&) override;
	virtual void heal(const double&);
	virtual bool inAttackRange(const Point&, const double&) const;
protected:
	double atk, healthMax;
	double moveRange, attackRange, moveSpeed;
	virtual int behavior() = 0;
	virtual int attack(EntityLiving*);
	virtual int move(const Point&);
};
