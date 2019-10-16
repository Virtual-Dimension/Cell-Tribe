#pragma once
#include "BaseTribe.h"
#include "../ItemManager.h"

constexpr int STATUS_WAIT = 0;

class PlayerTribe final : public BaseTribe {
public:
	PlayerTribe();
	PlayerTribe(const int& am, const int& st);
	~PlayerTribe();

	void addAmount(const int& x);
	void addStrength(const int& x);
protected:
	virtual int behavior() override;
	virtual int move(const Point& p) override;
	virtual int attack(BaseTribe*) override;
	virtual int forage() override;
private:
	int status;
	int energyMax, energy;
	ItemManager pack;

	/*int pickupItem(Item* item) {
		return pack.pushItem(item);
	}*/
};