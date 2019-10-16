#include "BaseTribe.h"

BaseTribe::BaseTribe() : BaseEntity(), amount(0), strength(0) {}

BaseTribe::~BaseTribe() {}

int BaseTribe::run() {
	if (amount <= 0) death = 1;
	if (death) return TRIBE_DEAD;

	int bh_res = behavior();
	if (bh_res != OPERATOR_SUCCESS) return bh_res;

	// more_opt
	return OPERATOR_SUCCESS;
}

void BaseTribe::beAttacked(BaseTribe* other, LL damage) {
	amount -= damage;
	if (amount <= 0) death = 1;
	return;
}

int BaseTribe::forage() { return OPERATOR_SUCCESS; }

int BaseTribe::propagate() { return OPERATOR_SUCCESS; }

int BaseTribe::inRange(const Point& p) const {
	for (const auto& cpoint : cellsPoint)
		if (abs(cpoint.x - p.x) < 1 && abs(cpoint.y - p.y) < 1) return 1;
	return abs(point.x - p.x) < 1 && abs(point.y - p.y) < 1;
}

LL BaseTribe::getAmount() const { return amount; }
LL BaseTribe::calcForce() const { return 1LL * amount * strength; }