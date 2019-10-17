#pragma once
#include "Entity/EntityPlayerTribe.h"
#include "Json/CJsonObject.h"
#include <vector>

struct Evolution {
	int    energyMax;
	int    cellsMax;

	double healthMax;
	double atk;
	double moveRange;
	double attackRange;
	double moveSpeed;
};

class EvolutionController {
private:
	neb::CJsonObject json;
public:
	EvolutionController();
	EvolutionController(const char*);
	void setEvolutionJson(const char*);
	Evolution getEvolution(const int&);
	~EvolutionController();
};