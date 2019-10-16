#pragma once

#include "game.h"
#include "Entity/BaseEntity.h"
#include <vector>

class BaseEntity;

class MapController {
	std::vector < BaseEntity* > entityList;
public:
	MapController();
	~MapController();
	void push(BaseEntity*);
	std::vector < BaseEntity* > get(const Point&) const;
	void erase(BaseEntity*);
	void erase(const size_t&);
};
