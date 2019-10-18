#pragma once

#include "Graph/slr.h"

class Entity;
class EventController;

class MapController :public SLObject {
	double mapBeginX, mapBeginY, mapEndX, mapEndY;
	std::vector < Entity* > entityList;
	std::vector < EventController*> ecList;
public:
	MapController(const double&, const double&, const double&, const double&);
	~MapController();
	int push(Entity*);
	int push(EventController*);
	virtual void update(double) override;
	std::vector < Entity* > get(const Point&) const;
	std::vector < Entity* > get(const Point&, const double&) const;
	const std::vector < Entity* >& getList() const;
	size_t count() const;
	int erase(Entity*);
	int erase(const size_t&);
	int erase(EventController*);
	bool exist(Entity*);
	bool beyond(const Point&) const;
	bool beyond(Entity*) const;
	Point getRightPoint() const;
};
