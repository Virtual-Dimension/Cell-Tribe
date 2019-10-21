#pragma once
#include "EntityLiving.h"
class SLDynamicPoint;
class EntityBaseTribe : public EntityLiving {
public:
	EntityBaseTribe();
	~EntityBaseTribe();
	virtual int spawn(MapController*)override;
	virtual int beAttacked(EntityLiving*, const double&) override;
	virtual void heal(const double&)override;
	virtual bool inRange(const Point&, const double&) const override;
protected:
	virtual int behavior() override;
	virtual int propagate();
	virtual int move(const Point&) override;
	virtual int attack(EntityLiving*) override;
	int energyMax, energy, cellsMax;
	double cellRadius, regeneration;
	struct CellPoint {
		SLDynamicPoint* point;
		double health;
	};
	std::list < CellPoint > cellsPoint;
	double moveCD, propagateCD;

};

