#include "MapController.h"

MapController::MapController(const double& bx, const double& by, const double& ex, const double& ey) : entityList(), mapBeginX(bx), mapBeginY(by), mapEndX(ex), mapEndY(ey) {}

MapController::~MapController() {}

int MapController::push(Entity* entity) {
	if (beyond(entity)) return OPERATOR_FAILED;
	entityList.push_back(entity);
	return OPERATOR_SUCCESS;
}

std::vector < Entity* > MapController::get(const Point& p) const {
	std::vector < Entity* > res;
	for (const auto& e : entityList)
		if (e->inRange(p)) res.push_back(e);
	return res;
}

std::vector<Entity*> MapController::get(const Point& p, const double& dis) const{
	std::vector < Entity* > res;
	for (const auto& e : entityList)
		if (e->inRange(p, dis)) res.push_back(e);
	return std::vector<Entity*>();
}

const std::vector<Entity*>& MapController::getList() const { return entityList; }

size_t MapController::count() const { return entityList.size(); }

int MapController::erase(Entity* entity) {
	for (std::vector < Entity* >::iterator e = entityList.begin(); e != entityList.end(); e++)
		if ((*e) == entity) {
			entityList.erase(e);
			return OPERATOR_SUCCESS;
		}
	return OPERATOR_FAILED;
}

int MapController::erase(const size_t& i) {
	if (i > entityList.size()) return OPERATOR_FAILED;
	entityList.erase(entityList.begin() + i);
	return OPERATOR_SUCCESS;
}

bool MapController::exist(Entity* entity) {
	for (std::vector < Entity* >::iterator e = entityList.begin(); e != entityList.end(); e++)
		if ((*e) == entity) return 1;
	return 0;
}

bool MapController::beyond(const Point& p) const {
	return p.x < mapBeginX || p.x > mapEndX || p.y < mapBeginY || p.y > mapEndY;
}

bool MapController::beyond(Entity* entity) const { return  beyond(entity->getPoint()); }

Point MapController::getRightPoint() const {
	double x = (1.0 * rand() / RAND_MAX) * (mapEndX - mapBeginX) + mapBeginX;
	double y = (1.0 * rand() / RAND_MAX) * (mapEndY - mapBeginY) + mapBeginY;
	return Point(x, y);
}

