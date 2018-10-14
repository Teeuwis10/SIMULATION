#include "EventManager.h"
#include "Road.h"
#include "Tools.h"
#include <iostream>
#include "Tools.h"
EventManager::EventManager()
{
}

EventManager::~EventManager()
{
}



void EventManager::spawnCar(std::string name, int position, int lenght, Road& road,std::string side, std::string roadname) {
	
	if (side == "RIGHT")
	{
		std::vector<RoadEvent>::iterator it;
		it = road.rightLines.at(0).Event.begin();
		it++;
		auto rng = Tools();
		road.rightLines.at(0).Event.insert(it, RoadEvent(name, position, lenght, rng.RandF(15, 25), 0, rng.RandF(5, 10), rng.RandF(5, 10), rng.RandF(90, 110),rng.RandF(0,3),roadname));
	}
	if (side == "LEFT")
	{

		std::vector<RoadEvent>::iterator it;
		it = road.leftLines.at(0).Event.begin();
		it++;
		auto rng = Tools();
		road.leftLines.at(0).Event.insert(it, RoadEvent(name, position, lenght, rng.RandF(15, 25), 0, rng.RandF(5, 10), rng.RandF(5, 10), rng.RandF(90, 110),rng.RandF(0,3), roadname));
	
	
		

	}


}
void EventManager::DriveStraright(std::vector<RoadEvent>::iterator& itt, std::vector<RoadEvent>& vec, int direction) {
	
		
		auto tmp = std::next(itt, 1);
		RoadEvent nextEvent = *tmp;
		RoadEvent currentEvent = *itt;
		///////////////////////////////////////////jazda prosto oraz jazda prosto z pierwszenstwem - 0 //// pozniej zamienic to w funkcje////////////////////////////////////////////////////////////////////////////
		Tools Tool;
		if (Tool.getDistance((*itt), nextEvent) + (*itt).curentSpeed >= 2)
		{
			bool cross = false;
			if (direction == 0 && nextEvent.name == "CROSS")
			{

				tmp = std::next(itt, 2);
				nextEvent = *tmp;
				cross = true;
			}
			if (Tool.getDistance(currentEvent, nextEvent) > 0)
			{
				if (Tool.getDistance(currentEvent, nextEvent) + (*itt).curentSpeed > (*itt).safeDistance)

				{
					if ((*itt).curentSpeed < (*itt).topSpeed)
					{
						(*itt).curentSpeed += (*itt).currentAcc;
						if ((*itt).curentSpeed > (*itt).topSpeed)
						{
							(*itt).curentSpeed = (*itt).topSpeed;
						}
					}

				}
				else if ((*itt).curentSpeed > 6)
				{
					int a = 0;
					//(*itt).curentSpeed -= (*itt).currentAcc;
					(*itt).curentSpeed -= 2;
					if ((*itt).curentSpeed < 0)
					{
						(*itt).curentSpeed = 0;
					}
				}

				if ((*itt).position + (*itt).lenght + (*itt).curentSpeed + 2 > nextEvent.position)
				{
					(*itt).curentSpeed = 0;
				}
				if ((*itt).curentSpeed < 3 && (*itt).position + (*itt).lenght + (*itt).curentSpeed + (*itt).currentAcc < nextEvent.position)

				{
					(*itt).curentSpeed += (*itt).currentAcc;
				}

				(*itt).Drive((*itt).curentSpeed);
				if (cross == true && (*itt).position + (*itt).curentSpeed >= (*std::next(itt, 1)).position)
				{
					std::cout << "Pojecha³em prosto z pierwszenstwem" << std::endl;
					iter_swap(itt, std::next(itt, 1));
					cross = false;
				}
			}
			
			//std::cout << std::setw(6)  << " " << std::setw(5) << (*itt).name << std::setw(10) << (*itt).position << std::setw(20) << Tool.getDistance((*itt), nextEvent)
			//<< " " << std::setw(5) << nextEvent.name << std::setw(5) << (*itt).curentSpeed << std::setw(5) << (*itt).currentAcc << std::setw(5) << (*itt).lenght << std::endl;
		
	};
}
void EventManager::insertCar( std::string name, int position, int lenght, Road& road, std::string side, std::string roadname) {
	if (side == "RIGHT") {
		std::vector<RoadEvent>::iterator it = road.rightLines.at(0).Event.begin();
		for (; it != road.rightLines.at(0).Event.end(); it++)
		{
			if ((*it).name == "CROSS")
			{
				break;

			}

		}
		auto rng = Tools();
		it++;
		road.rightLines.at(0).Event.insert(it, RoadEvent(name, position, lenght, rng.RandF(15, 25), 0, rng.RandF(5, 10), rng.RandF(5, 10), rng.RandF(90, 110),rng.RandF(0,3), roadname));

	}
	if (side == "LEFT")
	{
		std::vector<RoadEvent>::iterator it = road.leftLines.at(0).Event.begin();
		for (; it != road.leftLines.at(0).Event.end(); it++)
		{
			if ((*it).name == "CROSS")
			{
				break;

			}

		}
		auto rng = Tools();
		it++;
		road.leftLines.at(0).Event.insert(it, RoadEvent(name, position, lenght, rng.RandF(15, 25), 0, rng.RandF(5, 10), rng.RandF(5, 10), rng.RandF(5, 15),rng.RandF(0,3), roadname));
		
	}
	
}

void EventManager::insertCar(RoadEvent input,Road& road) {
	if (input.spawnLane.substr(3, input.spawnLane.length()) == "RIGHT") {
		std::vector<RoadEvent>::iterator it = road.rightLines.at(0).Event.begin();
		it++;
		auto rng = Tools();
		std::cout << " dzialam " << std::endl;
		std::cout << " dzialam " << input.name << " " << input.lenght << std::endl;
		system("pause");
		road.rightLines.at(0).Event.insert(it, RoadEvent(input.name, 0, input.lenght, rng.RandF(15, 25), 0, rng.RandF(5, 10), rng.RandF(5, 10), rng.RandF(90, 110), rng.RandF(0, 3), input.spawnLane));

	}
	if (input.spawnLane.substr(3, input.spawnLane.length()) == "LEFT") {
		std::vector<RoadEvent>::iterator it = road.leftLines.at(0).Event.begin();
		it++;
		auto rng = Tools();

		road.leftLines.at(0).Event.insert(it, RoadEvent(input.name, 0, input.lenght, rng.RandF(15, 25), 0, rng.RandF(5, 10), rng.RandF(5, 10), rng.RandF(90, 110), rng.RandF(0, 3), input.spawnLane));

	}

}

