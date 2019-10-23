#pragma once
#include "game.h"

struct Effect {
	double atk;
	double attackRange;
	int    cellsMax;
	double energyMax;
	double healthMax;
	double moveRange;
	double moveSpeed;
	double cellRadius;
	double regeneration;

	double moveNeed;
	double propagateNeed;
	double attackNeed;

};

struct Evolution {
	int id;
	std::string name;
	std::string describe;
};

class EvolutionController {
private:
	neb::CJsonObject json;
	int* got;
public:
	EvolutionController();
	EvolutionController(const char*);
	void initEvolutionJson(const char*);
	void gotEvolution(const int&);
	void getEvolutions(std::vector< Evolution>*, std::vector< Evolution>*);
	Effect getEvolutionEffect(const int&);
	~EvolutionController();
};