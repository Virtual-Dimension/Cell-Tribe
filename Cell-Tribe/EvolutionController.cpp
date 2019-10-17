#include "EvolutionController.h"


//Evolution::Evolution(const Info& minfo, EffectFunciton effectfunction) : info(minfo), effectFunction(effectfunction) {}
//
//Evolution::~Evolution() {}
//
//void Evolution::effect(EntityPlayerTribe* player) { effectFunction(player); }
//
//const Evolution::Info& Evolution::getInfo() { return info; }

EvolutionController::EvolutionController() : json() {}
EvolutionController::EvolutionController(const char* path) { setEvolutionJson(path); }

void EvolutionController::setEvolutionJson(const char* path) {
	char* res = new char[1024 * 32]();
	FILE* f = fopen(path, "r");
	if (f) {
		res[fread(res, 1, 1024 * 32, f)] = 0;
		fclose(f);
		json = neb::CJsonObject(res);
	}
	return;
}

void EvolutionController::updateEvolution(EntityPlayerTribe* player) {
	int length = json["evolutinos"].GetArraySize();
	for (int i = 0; i < length; i++) {

	}
}

EvolutionController::~EvolutionController() {}
