#include "Simulation.h"
#include "RoadBuilder.h"
#include "Road.h"
#include "ParamHolder.h"
#include <vector>
#include "RoadLine.h"
#include "RoadEvent.h"
#include "EventManager.h"
Simulation::Simulation()
{
}
void Simulation::StartSimulation(ParamHolder Paramiters)
{
	
	RoadBuilder tmp = RoadBuilder();
	Road Road = tmp.Build();
	EventManager eventManager = EventManager();


	for (int j = 0; j< 10; j++)
	{
		eventManager.spawnCar("CAR", 5, 1,Road);
	}
	while (true)
	{

		for (std::vector<RoadLine>::iterator it = Road.rightLines.begin(); it != Road.rightLines.end(); it++)
		{
			for (std::vector<RoadEvent>::iterator itt = (*it).Event.begin(); itt != (*it).Event.end(); itt++)
			{



				if ((*itt).name == "CAR")
				{

					(*itt).Drive();
				}



			}
			(*it).RoadLinePrint();


		}

	}
	
	
	
}

Simulation::~Simulation()
{
}
