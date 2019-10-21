#pragma once
#include "EntityLiving.h"

constexpr int STATUS_WAIT = 0;
constexpr int STATUS_ATTACK = 1;
constexpr int STATUS_USE = 2;

class EvolutionController;
class SLDynamicPoint;
struct Effect;

class EntityPlayerTribe final : public EntityLiving {
public:
	EntityPlayerTribe();
	EntityPlayerTribe(const std::string&, EvolutionController*);
	~EntityPlayerTribe();

	void addStrength(const int&); //tmp function
	void addEnergyMax(const int&);
	std::string getPlayerName() const;
	int beEffected(const Effect&);
	virtual int spawn(MapController*)override;
	virtual bool isPlayer() const override final;
protected:
	virtual int behavior() override;
	virtual int move(const Point&) override;
	virtual int attack(EntityLiving*) override;
	virtual int inRange(const Point&, const double&) const override;
	virtual int interact1(Entity*) override;
private:
	int propagate();
	int status;
	int energyMax, energy, cellsMax;
	double cellRadius, regeneration;
	std::list < SLDynamicPoint* > cellsPoint;
	int genePoints;
	std::string playerName;
	EvolutionController* evolutionController;
	double moveCD, propagateCD;
};