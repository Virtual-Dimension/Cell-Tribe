#pragma once
#include "EntityBaseTribe.h"

constexpr int STATUS_WAIT = 0;
constexpr int STATUS_ATTACK = 1;
constexpr int STATUS_USE = 2;

class EvolutionController;
class SLDynamicPoint;
struct Effect;

class EntityPlayerTribe : public EntityBaseTribe {
public:
	EntityPlayerTribe();
	EntityPlayerTribe(const std::string&, EvolutionController*);
	~EntityPlayerTribe();
	std::string getPlayerName() const;
	int beEffected(const Effect&);
	virtual bool isPlayer() const override final;
	virtual bool needEnergy() const override final;
protected:
	virtual int behavior() override;
	virtual int interact(Entity*) override;
private:
	int status;
	int genePoints;
	double moveNeed, propagateNeed, attackNeed;
	std::string playerName;
	EvolutionController* evolutionController;
};