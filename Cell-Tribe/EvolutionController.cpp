#include "EvolutionController.h"

Effect jsonToEvolutionEffect(neb::CJsonObject& effect) {
	Effect newEffect;
#define addval(str) (newEffect.str = 0),(effect.Get(#str, newEffect.str))
	addval(atk);
	addval(attackRange);
	addval(cellsMax);
	addval(energyMax);
	addval(healthMax);
	addval(moveRange);
	addval(moveSpeed);
	addval(cellRadius);
	addval(regeneration);
#undef addval
	return newEffect;
}

Evolution jsonToEvolution(neb::CJsonObject& evolution, int id = 0) {
	Evolution newEvolution;
#define addval(str) (evolution.Get(#str, newEvolution.str))
	addval(name);
	addval(describe);
#undef addval
	newEvolution.id = id;
	return newEvolution;
}

EvolutionController::EvolutionController() : json(), got(0) {}

EvolutionController::EvolutionController(const char* path) : json(), got(0) { initEvolutionJson(path); }

void EvolutionController::initEvolutionJson(const char* path) {
	char* res = new char[1024 * 32]();
	FILE* f = 0;
	fopen_s(&f, path, "r");
	if (f) {
		res[fread(res, 1, 1024 * 32, f)] = 0;
		fclose(f);
		json = neb::CJsonObject(res);
		if (got) delete got;
		got = new int[json["evolutinos"].GetArraySize() + 1]();
	}
	return;
}

void EvolutionController::gotEvolution(const int& x) { got[x] = 1; }

void EvolutionController::getEvolutions(std::vector<Evolution>* gotList, std::vector<Evolution>* canGotList) {
	if (!gotList && !canGotList) return;
	int len = json["evolutinos"].GetArraySize();
	for (int i = 0; i < len; i++) {
		if (got[i]) {
			if (gotList) gotList->push_back(jsonToEvolution(json["evolutinos"][i], i));
		}
		else if (canGotList) {
			int len2 = json["evolutinos"][i]["fa"].GetArraySize(), flag = 1;
			for (int j = 0, x = 0; j < len2 && flag; j++) {
				json["evolutinos"][i]["fa"].Get(j, x);
				if (!got[x]) flag = 0;
			}
			if (flag) canGotList->push_back(jsonToEvolution(json["evolutinos"][i], i));
		}
	}
}

Effect EvolutionController::getEvolutionEffect(const int& x) { return jsonToEvolutionEffect(json["evolutinos"][x]["effect"]); }

EvolutionController::~EvolutionController() {}
