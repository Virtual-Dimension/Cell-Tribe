#include "EntityPlayerTribe.h"

EntityPlayerTribe::EntityPlayerTribe() : EntityLiving(), energyMax(0), energy(0), status(STATUS_WAIT), genePoints(0) {}

EntityPlayerTribe::EntityPlayerTribe(const int& am) : EntityLiving(), energyMax(0), energy(0), status(STATUS_WAIT) { addCells(am); }

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
	printf("There are %lld cells.", cellsPoint.size());
	printf("OPT:");
	std::string opt;
	std::cin >> opt;
	if (opt == "attack") {
	}
	if (opt == "forge") {

	}
	if (opt == "add") {

	}
	return OPERATOR_SUCCESS;
}

int EntityPlayerTribe::attack(EntityLiving* other) {
	// other->beAttacked(this, atp);
	return OPERATOR_SUCCESS;
}

int EntityPlayerTribe::forage() {
	return OPERATOR_SUCCESS;
}

int EntityPlayerTribe::inRange(const Point& p) const {
	for (const auto& cpoint : cellsPoint)
		if (abs(cpoint.x - p.x) < 1 && abs(cpoint.y - p.y) < 1) return 1;
	return abs(point.x - p.x) < 1 && abs(point.y - p.y) < 1;
}