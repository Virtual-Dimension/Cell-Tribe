#pragma once

#include "game.h"
#include "BaseEntity.h"
#include <vector>

class BaseEntity;

class MapController {
	std::vector < BaseEntity* > entityList;
public:
	MapController();
	~MapController();
	void push(BaseEntity*);
	std::vector < BaseEntity* > get(const Point& p) const;
	void erase(BaseEntity*);
	void erase(const size_t& i);
};
