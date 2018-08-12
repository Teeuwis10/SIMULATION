#include "EventManager.h"
#include "Road.h"
#include "Tools.h"
EventManager::EventManager()
{
}

EventManager::~EventManager()
{
}



void EventManager::spawnCar(std::string name, int position, int lenght, Road& road) {
	std::vector<RoadEvent>::iterator it;
	it = road.rightLines.at(0).Event.begin();
	auto rng = Tools();
	
	road.rightLines.at(0).Event.insert(it, RoadEvent(name, position, lenght, rng.RandF(4, 5), 0, rng.RandF(1, 2), 0, rng.RandF(2, 5)));


}