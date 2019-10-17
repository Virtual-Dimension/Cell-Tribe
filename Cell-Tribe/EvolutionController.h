#pragma once
#include "Entity/EntityPlayerTribe.h"
#include "Json/CJsonObject.h"
#include <vector>
/*
typedef void (*EffectFunciton)(EntityPlayerTribe*);
class Evolution {
public:
	struct Info {
		std::string name;
		std::string describe;
		int needGenePoints;
	};
	Evolution(const Info&, EffectFunciton);
	~Evolution();
	const Info& getInfo();
	void effect(EntityPlayerTribe *) const;
private:
	Info info;
	EffectFunciton effectFunction;
};*/

class EvolutionController{
private:
	neb::CJsonObject json;
public:
	EvolutionController();
	EvolutionController(const char*);
	void setEvolutionJson(const char*);
	void updateEvolution(EntityPlayerTribe*);
	~EvolutionController();
};