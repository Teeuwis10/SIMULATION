#pragma once
#include <iostream>
#include "Road.h"
class EventManager
{
public:
	EventManager();
	~EventManager();
	void spawnCar(std::string name, int position, int lenght, Road& road, std::string side, std::string roadname);
	void insertCar(std::string name, int position, int lenght, Road& road,std::string side, std::string roadname);
	void insertCar(RoadEvent input, Road& road);
	void DriveStraright(std::vector<RoadEvent>::iterator& itt, std::vector<RoadEvent>& vec, int direction);
};
