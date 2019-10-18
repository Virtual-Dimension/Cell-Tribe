#pragma once

#include "game.h"
#include "Entity/Entity.h"

class Entity;

class MapController {
	double mapBeginX, mapBeginY, mapEndX, mapEndY;
	std::vector < Entity* > entityList;
public:
	MapController(const double&, const double&, const double&, const double&);
	~MapController();
	int push(Entity*);
	int update();
	std::vector < Entity* > get(const Point&) const;
	std::vector < Entity* > get(const Point&, const double&) const;
	const std::vector < Entity* >& getList() const;
	size_t count() const;
	int erase(Entity*);
	int erase(const size_t&);
	bool exist(Entity*);
	bool beyond(const Point&) const;
	bool beyond(Entity*) const;
	Point getRightPoint() const;
};
