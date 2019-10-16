#pragma once
#include "../game.h"
#include "../MapController.h"

class MapController;
class EntityLiving;

class Entity {
public:
	Entity();
	virtual ~Entity();
	virtual int run() = 0;
	int getDeath() const;
	LL getHealth() const;
	Point getPoint() const;
	virtual int inRange(const Point&) const;
	virtual void beAttacked(EntityLiving*, LL);
	virtual void beUsed(EntityLiving*);
protected:
	Point point;
	bool death, show;
	LL health;
	void setDeath();
	void setPoint(const Point&);
	void setShow(MapController*, const bool&);
	MapController* getMapController();
private:
	MapController* mapController;
};

