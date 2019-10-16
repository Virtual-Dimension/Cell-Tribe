#include "MapController.h"

MapController::MapController() : entityList() {}

MapController::~MapController() {}

void MapController::push(Entity* entity) { entityList.push_back(entity); }

std::vector < Entity* > MapController::get(const Point& p) const {
	std::vector < Entity* > res;
	for (const auto& e : entityList)
		if (e->inRange(p)) res.push_back(e);
	return res;
}

void MapController::erase(Entity* entity) {
	for (std::vector < Entity* >::iterator e = entityList.begin(); e != entityList.end(); e++)
		if ((*e) == entity) entityList.erase(e);
	return;
}

void MapController::erase(const size_t& i) { entityList.erase(entityList.begin() + i); }

