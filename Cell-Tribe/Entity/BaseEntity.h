#pragma once
#include "../game.h"
#include "../MapController.h"

class MapController;

class BaseEntity {
public:
	BaseEntity();
	virtual ~BaseEntity();
	virtual int run() = 0;
	int getDeath() const;
	Point getPoint() const;
	virtual int inRange(const Point&) const;
protected:
	Point point;
	bool death, show;
	void setDeath();
	void setPoint(const Point&);
	void setShow(MapController*, const bool&);
	MapController* getMapController();
private:
	MapController* mapController;
};

