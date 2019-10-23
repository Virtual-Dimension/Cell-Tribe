#pragma once

class MapController;

class EventController{
public:
	EventController(MapController*);
	~EventController();
	virtual void update();
	virtual void close();
	virtual void open();
private:
	MapController* mapController;
	double TribeUpdateCD;
	double EnergyUpdateCD;
};

