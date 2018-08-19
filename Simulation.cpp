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
	Road EASTROAD = tmp.BuildEast();
	Road SOUTHROAD = tmp.BuildSouth();
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
		bool bl = false;
		for (std::vector<RoadLine>::iterator it = EASTROAD.rightLines.begin(); it != EASTROAD.rightLines.end(); it++)
		{
			int a = 0;
			int lenght_ = 0;
			std::cout << "EASTROAD" << std::endl;
			for (std::vector<RoadEvent>::iterator itt = (*it).Event.begin(); itt != (*it).Event.end(); itt++)
			{
			

			
				if ((*itt).name == "CAR")

				{
					
					auto tmp = std::next(itt, 1);
					RoadEvent nextCar = *tmp;
					RoadEvent nextEvent = *tmp;
					RoadEvent currentEvent = *itt;
					/*while (true)
					{

						if (nextEvent.name == "CAR")
						{
							a++;

						}
						else
						{
							auto rmp2 = std::next(itt, a);
							nextEvent = *rmp2;
							break;
						}
					}


					//RoadEvent nextEvent

					/*if (nextEvent.name == "CROSS")       // jedz prosto
					{
						auto tmp = std::next(itt, 2);
						nextEvent = *tmp;
					}*/


					if (Tool.getDistance(currentEvent, nextEvent) > 0)
					{
						if (Tool.getDistance(currentEvent, nextEvent) + (*itt).curentSpeed > (*itt).safeDistance)

						{
							if ((*itt).curentSpeed < (*itt).topSpeed)
							{
								(*itt).curentSpeed++;
							}


						}
						else if ((*itt).curentSpeed > 0) (*itt).curentSpeed--;

						if ((*itt).position + (*itt).lenght + (*itt).curentSpeed + 2 > nextEvent.position)
						{
							(*itt).curentSpeed = 0;
						}

						(*itt).Drive((*itt).curentSpeed);

					}
					std::cout << "current event: " << currentEvent.position << ", distance to next" << Tool.getDistance(currentEvent, nextEvent) << std::endl;

					if (nextEvent.name == "CROSS" && Tool.getDistance((*itt), nextEvent) < 15)       // jedz w prawo
					{
						

						for (std::vector<RoadLine>::iterator ol = SOUTHROAD.rightLines.begin(); ol != SOUTHROAD.rightLines.end(); ol++)
						{
							
							for (std::vector<RoadEvent>::iterator oll = (*ol).Event.begin(); oll != (*ol).Event.end(); oll++)
							{


								if ((*oll).name == "CROSS")

								{
									auto tmp = std::next(oll, -1);
									auto tmp2 = std::next(oll, 1);
									RoadEvent prevEvent = *tmp;
									RoadEvent nextEvent1 = *tmp2;
									std::cout << "samochod z pierwszenstwem" << (*tmp).position << std::endl;
									if (prevEvent.position + prevEvent.lenght + prevEvent.curentSpeed + 3 > (*oll).position && Tool.getDistance((*oll),nextEvent1) < (10 + (*itt).lenght + (*itt).curentSpeed + (*itt).safeDistance))
									{
										(*itt).curentSpeed = 0;

									}
									else
									{
										//EASTROAD.rightLines.at(0).Event.erase(itt);
										//(*itt).curentSpeed = 5;
										//SOUTHROAD.rightLines.at(0).Event.insert(oll,eventManager.spawnCar("CAR" , std::abs((*itt).curentSpeed+(*itt).position-nextEvent.position)+(*oll).position,(*itt).lenght, SOUTHROAD ;
										//eventManager.spawnCar("CAR" , std::abs((*itt).curentSpeed+(*itt).position-nextEvent.position)+(*oll).position,(*itt).lenght, SOUTHROAD) ;
										//SOUTHROAD.rightLines.at(0).Event.insert(oll, *(itt));
										//(*ol).Event.insert(itt, 0);
										
										
										bl = true;
										 a = (*oll).position + std::abs((nextEvent.position - (*itt).position + (*itt).lenght) - (*itt).curentSpeed);
										 lenght_ = (*oll).lenght;
										 itt = (*it).Event.erase(itt);
										//eventManager.insertCar("CAR", 300, 10, SOUTHROAD);
										


										//(*itt).topSpeed = 0;
									}




								}
							}
							
						}
						
					}
				}
				
				
				
			}
			if (bl == true)
			{




				//eventManager.spawnCar("CAR", 300, 10, SOUTHROAD);
				//eventManager.insertCar("CAR", 300, 10, SOUTHROAD);
				//eventManager.insertCar("CAR", a, lenght_, SOUTHROAD);
				eventManager.insertCar("CAR", 501, 10, SOUTHROAD);



			}
			bl = false;
		//	(*it).Event.erase(((*it).Event.begin()));
			(*it).RoadLinePrint();

			
		}
		
		for (std::vector<RoadLine>::iterator tu = SOUTHROAD.rightLines.begin(); tu != SOUTHROAD.rightLines.end(); tu++)
		{
			std::cout << "size: " << (*tu).Event.size() << std::endl;
			for (std::vector<RoadEvent>::iterator tuu = (*tu).Event.begin(); tuu != (*tu).Event.end(); tuu++)
			{

				std::cout << "druga tablica: " << (*tuu).position << std::endl;
			}
			std::cout << "SOUTHROAD"  << std::endl;
			for (std::vector<RoadEvent>::iterator tuu= (*tu).Event.begin(); tuu != (*tu).Event.end(); tuu++)
			{
				
				for (std::vector<RoadLine>::iterator tu = SOUTHROAD.rightLines.begin(); tu != SOUTHROAD.rightLines.end(); tu++)
				{
				//	std::cout << "SOUTHROAD" << std::endl;
					
				}


				if ((*tuu).name == "CAR")

				{
					auto tmp = std::next(tuu, 1);
					RoadEvent nextEvent = *tmp;
					RoadEvent currentEvent = *tuu;


					if (Tool.getDistance(currentEvent, nextEvent)>0)
					{
						if (nextEvent.name == "RIGHT")
						{

						}
						if (Tool.getDistance(currentEvent, nextEvent) + (*tuu).curentSpeed > (*tuu).safeDistance)

						{
							if ((*tuu).curentSpeed < (*tuu).topSpeed)
							{
								(*tuu).curentSpeed++;
							}


						}
						else if ((*tuu).curentSpeed>0) (*tuu).curentSpeed--;

						if ((*tuu).position + (*tuu).lenght + (*tuu).curentSpeed + 2 > nextEvent.position)
						{
							(*tuu).curentSpeed = 0;
						}

						(*tuu).Drive((*tuu).curentSpeed);

					}
					std::cout << "current event: " << currentEvent.position << ", distance to next" << Tool.getDistance(currentEvent, nextEvent) << std::endl;

				}



			}
			(*tu).RoadLinePrint();


		}
	}
	
	
	
}

Simulation::~Simulation()
{
}
