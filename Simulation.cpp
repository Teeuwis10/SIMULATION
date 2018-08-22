#include "Simulation.h"
#include "RoadBuilder.h"
#include "Road.h"
#include "ParamHolder.h"
#include <iterator>
#include <vector>
#include "RoadLine.h"
#include "RoadEvent.h"
#include "EventManager.h"
#include "Tools.h"
#include <iostream>
#include <vector>
#include <iomanip>
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

/////////////////////////////////////////////////dodawanie samochod do drogi/////////////////////////////////////////
	for (int j = 0; j< 10; j++)
	{
		eventManager.spawnCar("CAR", 0, 10,EASTROAD,"RIGHT");
	}
	for (int j = 0; j< 10; j++)
	{
		eventManager.spawnCar("CAR", 0, 10, SOUTHROAD, "RIGHT");
	}
	for (int j = 0; j< 10; j++)
	{
		eventManager.spawnCar("CAR", 0, 10, SOUTHROAD, "LEFT");
	}
	for (int j = 0; j< 10; j++)
	{
		eventManager.spawnCar("CAR", 0, 10, SOUTHROAD, "LEFT");
	}
	
	while (true)
	{

		bool bl = false;
//////////////////////////////////////////////////////iterator pasow/////////////////////////////////////////////////
		for (std::vector<RoadLine>::iterator it = EASTROAD.rightLines.begin(); it != EASTROAD.rightLines.end(); it++)
		{
			int a = 0;
			int lenght_ = 0;
			
			std::cout << "EASTROAD---------------------------------------------------------------------------------------EASTROAD" << std::endl;
			std::cout << std::setw(10)<< "iterator"<< std::setw(20) << "current event" << std::setw(20) << "distance to next" << std::endl;
///////////////////////////////////////////////iterator eventow na pasie/////////////////////////////////////////////////
			for (std::vector<RoadEvent>::iterator itt = (*it).Event.begin(); itt != (*it).Event.end(); itt++)
			{
				
				int direction = Tool.RandF(0, 1);
				if ((*itt).name == "CAR")

				{
					
						auto tmp = std::next(itt, 1);
						RoadEvent nextEvent = *tmp;
						RoadEvent currentEvent = *itt;
///////////////////////////////////////////jazda prosto////////////////////////////////////////////////////////////////////////////
						if ( Tool.getDistance((*itt), nextEvent)+(*itt).curentSpeed >=15 )
						{

							if(direction == 1 && nextEvent.name == "CROSS")
							{
								tmp = std::next(itt, 2);
								nextEvent = *tmp;
							}
							if (Tool.getDistance(currentEvent, nextEvent) > 0 )
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
							
						}
						
////////////////////////////////////////////logika skretu w prawo///////////////////////////////////////////////////////////////
						if (nextEvent.name == "CROSS" && Tool.getDistance((*itt), nextEvent)+(*itt).curentSpeed < 15 && direction == 0)       // jedz w lewo
						{
							
							///////iterator po drodze w ktora skreca samochod//////////////////////////
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
										if ((prevEvent.position + prevEvent.lenght + prevEvent.curentSpeed + 3 > (*oll).position && Tool.getDistance((*oll), nextEvent1) < (10 + (*itt).lenght + (*itt).curentSpeed + (*itt).safeDistance))
											&&(Tool.turnLeftPrediction((*itt),nextEvent,prevEvent,(*oll))==true)
											)
										{
											(*itt).curentSpeed = 0;

										}
										else
										{
											bl = true;
											a = (*oll).position + std::abs((nextEvent.position - (*itt).position + (*itt).lenght) - (*itt).curentSpeed);
											lenght_ = (*oll).lenght;
											itt = (*it).Event.erase(itt);
											
										}

									}
								}

							}
						}
						auto index = std::distance((*it).Event.begin(), itt);
						std::cout <<std::setw(20)<< index <<std::setw(20) << currentEvent.position << std::setw(20) << Tool.getDistance(currentEvent, nextEvent) << std::endl;
				}
				
			}
/////////////////////////////dalej logika skretu w prawo///// dodanie samochodu do innej drogi/////////////////////////////////////////////////
			if (bl == true)
			{
				//eventManager.insertCar("CAR", a, lenght_, SOUTHROAD);
				eventManager.insertCar("CAR", 550, 10, SOUTHROAD);

			}
			bl = false;
			(*it).RoadLinePrint();

		}
		
		for (std::vector<RoadLine>::iterator tu = SOUTHROAD.rightLines.begin(); tu != SOUTHROAD.rightLines.end(); tu++)
		{
			
			std::cout << "SOUTHROAD|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||SOUTHROAD"  << std::endl;
			std::cout << std::setw(10) << "iterator" << std::setw(20) << "current event" << std::setw(20) << "distance to next" << std::endl;
			for (std::vector<RoadEvent>::iterator tuu= (*tu).Event.begin(); tuu != (*tu).Event.end(); tuu++)
			{
				
				if ((*tuu).name == "CAR")

				{
					auto tmp = std::next(tuu, 1);
					
					RoadEvent nextEvent = *tmp;
					
					RoadEvent currentEvent = *tuu;
					if (nextEvent.name == "CROSS"&&currentEvent.position>nextEvent.position)
					{
						tmp = std::next(tuu, 2);
						nextEvent = *tmp;
					}

					if (Tool.getDistance(currentEvent, nextEvent)>0)
					{
						
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
					auto index = std::distance((*tu).Event.begin(), tuu);
					std::cout << std::setw(20) << index << std::setw(20) << currentEvent.position << std::setw(20) << Tool.getDistance(currentEvent, nextEvent) <<nextEvent.name<< std::endl;

				}
				
			}
			(*tu).RoadLinePrint();

		}
	}
	
	
	
}

Simulation::~Simulation()
{
}
