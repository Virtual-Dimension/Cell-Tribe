#pragma once
#include "EntityBaseTribe.h"
class EntityMobTribe :	public EntityBaseTribe {
public:
	EntityMobTribe();
	~EntityMobTribe();
	virtual int behavior() override;
	virtual int interact(Entity* entity) override;
protected:
	virtual int move(const Point&) override;
private:
	Entity* atkEntity;
	double viewRange;
};

