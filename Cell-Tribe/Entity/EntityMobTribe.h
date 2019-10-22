#pragma once
#include "EntityBaseTribe.h"
class EntityMobTribe :	public EntityBaseTribe {
public:
	EntityMobTribe();
	EntityMobTribe(const Point&);
	~EntityMobTribe();
	virtual int behavior() override;
	virtual int beAttacked(EntityLiving*) override;
	virtual int interact(Entity*) override;
protected:
	virtual int move(const Point&) override;
private:
	Entity* atkEntity;
	double viewRange;
};

