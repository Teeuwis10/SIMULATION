#pragma once
#include <iostream>
#include "Road.h"
class EventManager
{
public:
	EventManager();
	~EventManager();
	void spawnCar(std::string name, int position, int lenght, Road& road, std::string side);
	void insertCar(std::string name, int position, int lenght, Road& road,std::string side);
};
