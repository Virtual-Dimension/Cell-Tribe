#pragma once
#include "MapController.h"

class EventController{
public:
	EventController(const MapController*);
	~EventController();
	void update();
private:
	const MapController* mapController;
	
};

