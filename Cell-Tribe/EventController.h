#pragma once

class MapController;

class EventController{
public:
	EventController(MapController*);
	~EventController();
	void update();
	void close();
	void open();
private:
	MapController* mapController;
	
};

