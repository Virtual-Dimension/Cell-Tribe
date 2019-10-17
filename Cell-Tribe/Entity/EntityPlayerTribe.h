#pragma once
#include "EntityLiving.h"
#include "EntityItem.h"

constexpr int STATUS_WAIT = 0;
constexpr int STATUS_ATTACK = 1;
constexpr int STATUS_USE = 2;

class EntityPlayerTribe final : public EntityLiving {
public:
	EntityPlayerTribe();
	EntityPlayerTribe(const std::string&);
	~EntityPlayerTribe();

	void addCells(const int&);
	void addStrength(const int&);
	void addEnergyMax(const int&);
	std::string getPlayerName() const;
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
	double moveRange;
	double attackRange;
	std::string playerName;
	EvolutionController* evolutionController;
};