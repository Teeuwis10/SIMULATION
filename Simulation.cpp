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
#include <Windows.h>
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
		eventManager.spawnCar("CAR", 0, 10, EASTROAD, "LEFT");
	}
	for (int j = 0; j< 10; j++)
	{
		eventManager.spawnCar("CAR", 0, 10, SOUTHROAD, "LEFT");
	}
	
	while (true)
	{

		bool bl = false;
//////////////////////////////////////////////////////iterator pasow (przygotowane dla domyslnie jedenego pasa)//////////////////////////////////////////////////////////
		for (std::vector<RoadLine>::iterator it = EASTROAD.rightLines.begin(); it != EASTROAD.rightLines.end(); it++)
		{
			//zmienne samochodu do przeniesienia na inna liste
			int a = 0;
			int lenght_ = 0;
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, 10);
			std::cout << "EASTROAD-----------------------------------RIGHT----------------------------------------------------EASTROAD" << std::endl;
			std::cout << std::setw(10) << "iterator" << std::setw(20) << "current event" << std::setw(20)<< "lenght" << std::setw(20) << "distance to next" << std::endl;
///////////////////////////////////////////////iterator eventow na pasie/////////////////////////////////////////////////
			for (std::vector<RoadEvent>::iterator itt = (*it).Event.begin(); itt != (*it).Event.end(); itt++)
			{
				if ((*itt).name == "CROSS")
				{
					//std::cout << "dlaczego mi to robisz" << std::endl;
					std::cout << (*itt).position << std::endl;
				}
				int direction = Tool.RandF(0, 1);   //pozniej tutaj funkcja sterujaca zachowaniem samochodow na skrzyzowaniu
				direction = 0;
				if ((*itt).name == "CAR")

				{
						auto tmp = std::next(itt, 1);
						RoadEvent nextEvent = *tmp;
						RoadEvent currentEvent = *itt;
///////////////////////////////////////////jazda prosto//// pozniej zamienic to w funkcje////////////////////////////////////////////////////////////////////////////
						//if (nextEvent.position != 500 && nextEvent.name == "CROSS")
						
						
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
						
////////////////////////////////////////////logika skretu w lewo///////// jesli sie da zapakowac do fukcji///////////////////////////////////////////////////////////////
						if (nextEvent.name == "CROSS" && Tool.getDistance((*itt), nextEvent)+(*itt).curentSpeed < 15 && direction == 0)       // jedz w lewo
						{
							std::cout << "SOUTHROAD, RIGHT" << std::endl;
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
											//std::cout << "SOUTHROAD, RIGHT dlugosc" << lenght_ << std::endl;
											a = (*oll).position + std::abs((nextEvent.position - (*itt).position + (*itt).lenght) - (*itt).curentSpeed);
											lenght_ = (*itt).lenght;
											//std::cout << "SOUTHROAD, RIGHT dlugosc" << (*itt).name <<"  " <<(*itt).lenght << std::endl;
											//std::cout << "SOUTHROAD, RIGHT dlugosc" << lenght_ << std::endl;
											itt = (*it).Event.erase(itt);
											

										}

									}
								}

							}
						}
						int index = std::distance((*it).Event.begin(), itt);
						//it--;
						//	itt--;
						
						//itt--;
						//std::vector<RoadLine>::iterator test = (*it).Event.end();
						//itt = (*it).Event.end();
						int index1 = std::distance((*it).Event.begin(), (*it).Event.end());
						std::cout << std::setw(10) << index << std::setw(20) << currentEvent.position << std::setw(20) << currentEvent.lenght << " " << currentEvent.name << std::setw(20) << Tool.getDistance(currentEvent, nextEvent) << " " << nextEvent.name << std::endl;
						if (index1-3 == index)
						{
							(*it).RoadLinePrint();
						}
						
					//itt++;
				}
				
			}
			
/////////////////////////////dalej logika skretu w lewo///// dodanie samochodu do innej drogi/////////////////////////////////////////////////
			if (bl == true)
			{
				//std::cout << "SOUTHROAD, RIGHT" << std::endl;
				//std::cout << "SOUTHROAD, RIGHT dlugosc"<< lenght_ << std::endl;
				eventManager.insertCar("CAR", a, lenght_, SOUTHROAD, "RIGHT");
				//eventManager.insertCar("CAR", a, 10, SOUTHROAD, "RIGHT");
				
			}
			bl = false;
			
			
			SetConsoleTextAttribute(hConsole, 15);
		}
		///////////////////////////////////////lewy pas EASTROAD//////////////////////////////////////////////////////////////////
		bool b2 = false; 
		
		//////////////////////////////////////////////////////iterator pasow /////////////////////////////////////////////////
		for (std::vector<RoadLine>::iterator it = EASTROAD.leftLines.begin(); it != EASTROAD.leftLines.end(); it++)
		{
			int a = 0;
			int lenght_ = 0;

			std::cout << "EASTROAD------------------------------------LEFT---------------------------------------------------EASTROAD" << std::endl;
			std::cout << std::setw(10) << "iterator" << std::setw(20) << "current event" << std::setw(20) << "distance to next" << std::endl;
			///////////////////////////////////////////////iterator eventow na pasie/////////////////////////////////////////////////
			for (std::vector<RoadEvent>::iterator itt = (*it).Event.begin(); itt != (*it).Event.end(); itt++)
			{
			//	std::cout << "TEST" << (*itt).name << std::endl;
				int direction = Tool.RandF(0, 1);
				//direction = 0;
				if ((*itt).name == "CAR")

				{
					
					auto tmp = std::next(itt, 1);
					RoadEvent nextEvent = *tmp;
					RoadEvent currentEvent = *itt;
					///////////////////////////////////////////jazda prosto////////////////////////////////////////////////////////////////////////////
					if (Tool.getDistance((*itt), nextEvent) + (*itt).curentSpeed >= 15)
					{

						if (direction == 1 && nextEvent.name == "CROSS")
						{
							tmp = std::next(itt, 2);
							nextEvent = *tmp;
						}
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

					}

					////////////////////////////////////////////logika skretu w lewo///////////////////////////////////////////////////////////////
					if (nextEvent.name == "CROSS" && Tool.getDistance((*itt), nextEvent) + (*itt).curentSpeed < 15 && direction == 0)       // jedz w lewo
					{
						
						///////iterator po drodze w ktora skreca samochod//////////////////////////
						for (std::vector<RoadLine>::iterator ol = SOUTHROAD.leftLines.begin(); ol != SOUTHROAD.leftLines.end(); ol++)
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
										&& (Tool.turnLeftPrediction((*itt), nextEvent, prevEvent, (*oll)) == true)
										)
									{
										(*itt).curentSpeed = 0;

									}
									else
									{
										b2 = true;
										a = (*oll).position + std::abs((nextEvent.position - (*itt).position + (*itt).lenght) - (*itt).curentSpeed);
										lenght_ = (*oll).lenght;
										itt = (*it).Event.erase(itt);

									}

								}
							}

						}
					}
					
					auto index = std::distance((*it).Event.begin(), itt);
					//std::cout << std::setw(20) << index << std::setw(20) << currentEvent.position << std::setw(20) << Tool.getDistance(currentEvent, nextEvent) << std::endl;
					std::cout << std::setw(10) << index << std::setw(20) << currentEvent.position + currentEvent.lenght << " " << currentEvent.name << std::setw(20) << Tool.getDistance(currentEvent, nextEvent) << " " << nextEvent.name << std::endl;
				}

			}

			/////////////////////////////dalej logika skretu w prawo///// dodanie samochodu do innej drogi/////////////////////////////////////////////////
			if (b2 == true)
			{
				
			eventManager.insertCar("CAR", a, lenght_, SOUTHROAD, "LEFT");
				//eventManager.insertCar("CAR", a, 10, SOUTHROAD, "LEFT");
			//	eventManager.insertCar("CAR", 550, 10, SOUTHROAD,"LEFT");

			}
			b2 = false;
			(*it).RoadLinePrint();
		
		}
		
		for (std::vector<RoadLine>::iterator tu = SOUTHROAD.rightLines.begin(); tu != SOUTHROAD.rightLines.end(); tu++)
		{
			int index1;
			int index;
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
					//auto index = std::distance((*tu).Event.begin(), tuu);
					//std::cout << std::setw(10) << index << std::setw(20) << currentEvent.position + currentEvent.lenght << " " << currentEvent.name << std::setw(20) << Tool.getDistance(currentEvent, nextEvent) << " " << nextEvent.name << std::endl;
				//	(*tu).RoadLinePrint();

					 index = std::distance((*tu).Event.begin(), tuu);
					//it--;
					//	itt--;

					//itt--;
					//std::vector<RoadLine>::iterator test = (*it).Event.end();
					//itt = (*it).Event.end();
					 index1 = std::distance((*tu).Event.begin(), (*tu).Event.end());
					std::cout << std::setw(10) << index << std::setw(20) << currentEvent.position + currentEvent.lenght << " " << currentEvent.name << std::setw(20) << Tool.getDistance(currentEvent, nextEvent) << " " << nextEvent.name << std::endl;
					if (index1 - 3 == index)
					{
					(*tu).RoadLinePrint();
					}
					
				}
				
				
			}
			for (std::vector<RoadLine>::iterator tu = SOUTHROAD.rightLines.begin(); tu != SOUTHROAD.rightLines.end(); tu++)
			{
				int index1;
				int index;
				std::cout << "TEST" << std::endl;
				std::cout << std::setw(10) << "iterator" << std::setw(20) << "current event" << std::setw(20) << "distance to next" << std::endl;
				for (std::vector<RoadEvent>::iterator tuu = (*tu).Event.begin(); tuu != (*tu).Event.end(); tuu++)
				{
					index = std::distance((*tu).Event.begin(), tuu);
					//it--;
					//	itt--;
					std::cout << (*tuu).name << " " << (*tuu).position << std::endl;
					
					//itt--;
					//std::vector<RoadLine>::iterator test = (*it).Event.end();
					//itt = (*it).Event.end();
					index1 = std::distance((*tu).Event.begin(), (*tu).Event.end());
					
					//std::cout << std::setw(10) << index << std::setw(20) << currentEvent.position + currentEvent.lenght << " " << currentEvent.name << std::setw(20) << Tool.getDistance(currentEvent, nextEvent) << " " << nextEvent.name << std::endl;
					if (index1 - 3 == index)
					{
						
					}
				}
				(*tu).RoadLinePrint();
			}
			

		}
	}
	
	
	
}

Simulation::~Simulation()
{
}
