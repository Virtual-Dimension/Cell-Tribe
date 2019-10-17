#include "EntityPlayerTribe.h"

EntityPlayerTribe::EntityPlayerTribe() : EntityLiving(), energyMax(0), energy(0), status(STATUS_WAIT), genePoints(0) {
	health = 5;
}

EntityPlayerTribe::EntityPlayerTribe(const int& am) : EntityLiving(), energyMax(0), energy(0), status(STATUS_WAIT) { 
	addCells(am);
	health = 5;
}

EntityPlayerTribe::~EntityPlayerTribe() {}

void EntityPlayerTribe::addCells(const int& val) {
	for (int i= 0; i < val; i++) cellsPoint.push_back(Point(0, 0));
	return;
}

void EntityPlayerTribe::addStrength(const int& val) { atp += val; }

int EntityPlayerTribe::move(const Point& p) {
	// API
	return OPERATOR_SUCCESS;
}

int EntityPlayerTribe::behavior() {
	// wait for player
	if (cellsPoint.size() == 0) {
		health = 0;
		return ENTITY_DEAD;
	}
	printf("There are %lld cells.", cellsPoint.size());
	printf("OPT:");
	std::string opt;
	while (true) {
		std::cin >> opt;
		if (opt == "attack") {
			std::cin >> opt;
		}
		if (opt == "forge") {

		}
		if (opt == "add") {

		}
		if (opt == "list") {

		}
		if (opt == "exit") {
			break;
		}
	}
	
	return OPERATOR_SUCCESS;
}

int EntityPlayerTribe::attack(EntityLiving* other) {
	// other->beAttacked(this, atp);
	return OPERATOR_SUCCESS;
}


int EntityPlayerTribe::inRange(const Point& p) const {
	for (const auto& cpoint : cellsPoint)
		if (abs(cpoint.x - p.x) < 1 && abs(cpoint.y - p.y) < 1) return 1;
	return abs(getPoint().x - p.x) < 1 && abs(getPoint().y - p.y) < 1;
}

int EntityPlayerTribe::interact1(Entity* entity){
	if (entity->canBeUsed()) {
		entity->beUsed(this);
		return ITEM_USED;
	}
	if (entity->canBeAttacked()) {
		this->attack((EntityLiving*)entity);
		return ITEM_USED;
	}
	return 0;
}
