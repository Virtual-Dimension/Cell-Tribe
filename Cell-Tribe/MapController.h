#pragma once

#include "game.h"
#include "Entity/Entity.h"
#include <vector>

class Entity;

class MapController {
	double mapBeginX, mapBeginY, mapEndX, mapEndY;
	std::vector < Entity* > entityList;
public:
	MapController(const double&, const double&, const double&, const double&);
	~MapController();
	int push(Entity*);
	std::vector < Entity* > get(const Point&) const;
	int erase(Entity*);
	int erase(const size_t&);
	bool count(Entity*);
	int beyond(const Point&) const;
	int beyond(Entity*) const;
	Point getRightPoint() const;
};
