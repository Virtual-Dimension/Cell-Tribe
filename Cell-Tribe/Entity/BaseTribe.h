#pragma once
#include "BaseEntity.h"

class BaseTribe : public BaseEntity {
public:
	BaseTribe();
	~BaseTribe();
	virtual int run() override final;
	virtual void beAttacked(BaseTribe*, LL);
	virtual int inRange(const Point& p) const override;
	LL getAmount() const;
	LL calcForce() const;
protected:
	LL amount, strength;
	std::vector < Point > cellsPoint;
	virtual int behavior() = 0;
	virtual int move(const Point& p) = 0;
	virtual int attack(BaseTribe*) = 0;
	virtual int propagate();
	virtual int forage();
};
