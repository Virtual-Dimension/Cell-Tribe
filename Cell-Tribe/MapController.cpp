#include "MapController.h"

MapController::MapController() : entityList() {}

MapController::~MapController() {}

void MapController::push(BaseEntity* entity) { entityList.push_back(entity); }

std::vector < BaseEntity* > MapController::get(const Point& p) const {
	std::vector < BaseEntity* > res;
	for (const auto& e : entityList)
		if (e->inRange(p)) res.push_back(e);
	return res;
}

void MapController::erase(BaseEntity* entity) {
	for (std::vector < BaseEntity* >::iterator e = entityList.begin(); e != entityList.end(); e++)
		if ((*e) == entity) entityList.erase(e);
	return;
}

void MapController::erase(const size_t& i) { entityList.erase(entityList.begin() + i); }

