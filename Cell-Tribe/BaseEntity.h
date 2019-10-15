#pragma once
#include "game.h"
#include "MapController.h"
class MapController;
class BaseEntity {
protected:
	MapController* mapController;
	Point point;
	bool death, show;
	void setDeath();
	void setPoint();
	void setShow(MapController* mapcontroller, const bool& x);
public:
	BaseEntity();
	virtual ~BaseEntity();
	virtual int run() = 0;
	int getDeath() const;
	Point getPoint() const;
	virtual int inRange(const Point& p) const;
};

