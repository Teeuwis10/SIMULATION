#include "Simulation.h"
#include "RoadBuilder.h"
#include "Road.h"
#include "ParamHolder.h"
#include <vector>
#include "RoadLine.h"
#include "RoadEvent.h"
#include "EventManager.h"
#include "Tools.h"
Simulation::Simulation()
{
}
void Simulation::StartSimulation(ParamHolder Paramiters)
{
	Tools Tool = Tools();
	RoadBuilder tmp = RoadBuilder();
	RoadBuilder tmp2 = RoadBuilder();
	Road EASTROAD = tmp.Build();
	Road SOUTHROAD = tmp.Build();
	EventManager eventManager = EventManager();


	for (int j = 0; j< 10; j++)
	{
		eventManager.spawnCar("CAR", 0, 10,EASTROAD);
	}
	for (int j = 0; j< 10; j++)
	{
		eventManager.spawnCar("CAR", 0, 10, SOUTHROAD);
	}
	
	while (true)
	{

		for (std::vector<RoadLine>::iterator it = EASTROAD.rightLines.begin(); it != EASTROAD.rightLines.end(); it++)
		{
			for (std::vector<RoadEvent>::iterator itt = (*it).Event.begin(); itt != (*it).Event.end(); itt++)
			{
			

				if ((*itt).name == "CAR")
	
				{
					auto tmp = std::next(itt, 1);
					RoadEvent nextEvent = *tmp;
					RoadEvent currentEvent = *itt;
			
					
					if (Tool.getDistance(currentEvent, nextEvent)>0)
					{
						if (nextEvent.name == "RIGHT")
						{
							
						}
						if (Tool.getDistance(currentEvent, nextEvent)+(*itt).curentSpeed > (*itt).safeDistance)
					
						{
							if ((*itt).curentSpeed < (*itt).topSpeed)
							{
								(*itt).curentSpeed++;
							}

							
						}
						else if((*itt).curentSpeed>0) (*itt).curentSpeed--;
						
						if ((*itt).position+(*itt).lenght + (*itt).curentSpeed +2 > nextEvent.position)
						{
							(*itt).curentSpeed = 0;
						}

						(*itt).Drive((*itt).curentSpeed);

					}
					std::cout << "current event: " << currentEvent.position << ", distance to next" << Tool.getDistance(currentEvent, nextEvent) << std::endl;
										
				}
				


			}
			(*it).RoadLinePrint();


		}

	}
	
	
	
}

Simulation::~Simulation()
{
}
