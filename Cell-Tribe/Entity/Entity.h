#pragma once
#include "../game.h"
#include "../MapController.h"

constexpr int ENTITY_EXIST = -3;
constexpr int ENTITY_DEAD = -2;
constexpr int ITEM_USED = 2;



class MapController;
class EntityLiving;

class Entity {
public:
	Entity();
	virtual ~Entity();
	virtual int update() = 0;
	int getDeath() const;
	LL getHealth() const;
	Point getPoint() const;
	virtual int inRange(const Point&) const;
	virtual bool canBeAttacked() const;
	virtual int beAttacked(EntityLiving*, const LL&);
	virtual bool canBeUsed() const;
	virtual int beUsed(EntityLiving*);
	virtual int respawn(MapController*);
protected:
	LL health;
	void setPoint(const Point&);
	void setDeath();
	void setShow(MapController*, const bool&);
	MapController* getMapController();
private:
	Point point;
	MapController* mapController;
	bool death, show;
};

