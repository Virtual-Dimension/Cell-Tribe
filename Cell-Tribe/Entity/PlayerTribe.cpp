#include "PlayerTribe.h"

PlayerTribe::PlayerTribe() : BaseTribe(), energyMax(0), energy(0), status(STATUS_WAIT), pack(64) {}

// cpp

//

PlayerTribe::PlayerTribe(const int& am, const int& st) : BaseTribe(), energyMax(0), energy(0), status(STATUS_WAIT), pack(64) { amount=am, strength=st; }

PlayerTribe::~PlayerTribe() {}

void PlayerTribe::addAmount(const int& val) { amount += val; }

void PlayerTribe::addStrength(const int& val) { strength += val; }

int PlayerTribe::move(const Point& p) {
	// API
	return OPERATOR_SUCCESS;
}

int PlayerTribe::behavior() {
	// wait for player
	printf("There are %lld cells.", amount);
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

int PlayerTribe::attack(BaseTribe* other) {
	LL damage = calcForce() / (other->getAmount() + 1) + 1;
	other->beAttacked(this, damage);
	return OPERATOR_SUCCESS;
}

int PlayerTribe::forage() {
	return OPERATOR_SUCCESS;
}