#include "Simulation.h"
#include "RoadBuilder.h"
#include "Road.h"
#include "ParamHolder.h"
#include <vector>
#include "RoadLine.h"

Simulation::Simulation()
{
}
void Simulation::StartSimulation(ParamHolder Paramiters)
{
	
	RoadBuilder tmp = RoadBuilder();
	Road Road = tmp.Build();


	for (int i = 0; i < 10; i++)
	{
		Road.spawnCar("CAR",5, 1);
	}
	
	while (true)
	{

		for (std::vector<RoadLine>::iterator it = Road.rightLines.begin(); it != Road.rightLines.end(); it++)
		{
			for (std::vector<RoadEvent>::iterator itt = (*it).Event.begin(); itt != (*it).Event.end(); itt++)
			{

				RoadEvent & Test = (*itt);
				
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
