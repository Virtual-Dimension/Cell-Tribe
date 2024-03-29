#pragma once
#include "EntityLiving.h"

class SLDynamicPoint;
class EntityBaseTribe : public EntityLiving {
public:
	EntityBaseTribe();
	~EntityBaseTribe();
	virtual int onSpawning(MapController*)override;
	virtual int beAttacked(EntityLiving*) override;
	virtual double getAttackDamage(const Point&, const double&) override;
	virtual void heal(const double&)override;
	virtual bool inRange(const Point&, const double&) const override;
	virtual void showAttackRange() const override;
protected:
	virtual int behavior() override;
	virtual int propagate();
	virtual int move(const Point&) override;
	int cellsMax;
	double cellRadius, regeneration;
	struct CellPoint {
		SLDynamicPoint* point;
		double health;
	};
	std::list < CellPoint > cellsPoint;
	double moveCD, propagateCD;
	double pointColor;
};

