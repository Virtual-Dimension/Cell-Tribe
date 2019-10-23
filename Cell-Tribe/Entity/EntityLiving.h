#pragma once
#include "Entity.h"

class EntityLiving : public Entity {
public:
	EntityLiving();
	~EntityLiving();
	virtual int update() override final;
	virtual bool canBeAttacked() const override final;
	virtual int beAttacked(EntityLiving*) override;
	virtual double getAttackDamage(const Point&, const double&);
	virtual void heal(const double&);
	virtual bool needEnergy() const;
	virtual void energyUp(const double&);
protected:
	double energyMax, energy;
	double atk, healthMax;
	double moveRange, attackRange, moveSpeed;
	virtual int behavior() = 0;
	virtual int attack(EntityLiving*);
	virtual int move(const Point&);
};
