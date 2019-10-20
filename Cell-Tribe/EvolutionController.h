#pragma once
#include "game.h"

struct Effect {
	int    energyMax;
	int    cellsMax;

	double healthMax;
	double atk;
	double moveRange;
	double attackRange;
	double moveSpeed;
	double cellRadius;
	double regeneration;
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