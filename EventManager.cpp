#include "EventManager.h"
#include "Road.h"
#include "Tools.h"
#include <iostream>
EventManager::EventManager()
{
}

EventManager::~EventManager()
{
}



void EventManager::spawnCar(std::string name, int position, int lenght, Road& road,std::string side) {
	
	if (side == "RIGHT")
	{
		std::vector<RoadEvent>::iterator it;
		it = road.rightLines.at(0).Event.begin();
		it++;
		auto rng = Tools();
		road.rightLines.at(0).Event.insert(it, RoadEvent(name, position, lenght, rng.RandF(15, 25), 0, rng.RandF(2, 4), 0, rng.RandF(5, 10)));
	}
	else
	{

		std::vector<RoadEvent>::iterator it;
		it = road.leftLines.at(0).Event.begin();
		it++;
		auto rng = Tools();
		road.leftLines.at(0).Event.insert(it, RoadEvent(name, position, lenght, rng.RandF(15, 25), 0, rng.RandF(2, 4), 0, rng.RandF(5, 10)));

	}


}

void EventManager::insertCar( std::string name, int position, int lenght, Road& road) {
	std::vector<RoadEvent>::iterator it = road.rightLines.at(0).Event.begin();
	for (; it != road.rightLines.at(0).Event.end(); it++)
	{
		if ((*it).name == "CROSS")
		{
			break;
			
		}
		
	}
	auto rng = Tools();
	//it++;
	road.rightLines.at(0).Event.insert(it, RoadEvent(name, position, lenght, rng.RandF(15, 25), 0, rng.RandF(2, 4), 0, rng.RandF(5, 10)));


}

