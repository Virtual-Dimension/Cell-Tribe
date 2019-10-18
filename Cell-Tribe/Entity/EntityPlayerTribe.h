#pragma once
#include "EntityLiving.h"

constexpr int STATUS_WAIT = 0;
constexpr int STATUS_ATTACK = 1;
constexpr int STATUS_USE = 2;

class EvolutionController;
struct Effect;

class EntityPlayerTribe final : public EntityLiving {
public:
	EntityPlayerTribe();
	EntityPlayerTribe(const std::string&, EvolutionController*);
	~EntityPlayerTribe();

	int addCells(const int&); //tmp function
	void addStrength(const int&); //tmp function
	void addEnergyMax(const int&);
	std::string getPlayerName() const;
	int beEffected(const Effect&);
	virtual bool isPlayer() const override final;

protected:
	virtual int behavior() override;
	virtual int move(const Point&) override;
	virtual int attack(EntityLiving*) override;
	virtual int inRange(const Point&) const override;
	virtual int interact1(Entity*) override;
	virtual int print() const override;
private:
	int status;
	int energyMax, energy, cellsMax;
	std::vector < Point > cellsPoint;
	int genePoints;
	std::string playerName;
	EvolutionController* evolutionController;
};