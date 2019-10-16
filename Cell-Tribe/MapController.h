#pragma once

#include "game.h"
#include "Entity/Entity.h"
#include <vector>

class Entity;

class MapController {
	std::vector < Entity* > entityList;
public:
	MapController();
	~MapController();
	void push(Entity*);
	std::vector < Entity* > get(const Point&) const;
	void erase(Entity*);
	void erase(const size_t&);
};
