#include "EvolutionController.h"


Evolution jsonToEvolution(neb::CJsonObject& effect) {
	Evolution newEvolution;
	memset(&newEvolution, 0, sizeof(newEvolution));
#define addval(str) (effect.Get(#str, newEvolution.str))
	addval(atk);
	addval(attackRange);
	addval(cellsMax);
	addval(energyMax);
	addval(healthMax);
	addval(moveRange);
	addval(moveSpeed);
#undef getval
	return newEvolution;
}

EvolutionController::EvolutionController() : json() {}

EvolutionController::EvolutionController(const char* path) : json() { setEvolutionJson(path); }

void EvolutionController::setEvolutionJson(const char* path) {
	char* res = new char[1024 * 32]();
	FILE* f = fopen(path, "r");
	if (f) {
		res[fread(res, 1, 1024 * 32, f)] = 0;
		fclose(f);
		json = neb::CJsonObject(res);
		// unfinished
	}
	return;
}

Evolution EvolutionController::getEvolution(const int& x) {
	return jsonToEvolution(json["evolutinos"][x]);
}

EvolutionController::~EvolutionController() {}
