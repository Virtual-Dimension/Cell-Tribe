#pragma once
#include "EntityLiving.h"
#include "EntityItem.h"

constexpr int STATUS_WAIT = 0;



class EntityPlayerTribe final : public EntityLiving {
public:
	EntityPlayerTribe();
	EntityPlayerTribe(const int&);
	~EntityPlayerTribe();

	void addCells(const int&);
	void addStrength(const int&);
protected:
	virtual int behavior() override;
	virtual int move(const Point&) override;
	virtual int attack(EntityLiving*) override;
	virtual int inRange(const Point&) const override;
	virtual int interact1(Entity*) override;
private:
	int status;
	int energyMax, energy;
	std::vector < Point > cellsPoint;
	int genePoints;
};