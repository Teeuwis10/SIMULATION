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
#include "ConsolColor.h"

Simulation::Simulation()
{
}
void Simulation::StartSimulation(ParamHolder Paramiters)
{
	Tools Tool = Tools();
	RoadBuilder tmp = RoadBuilder();
	RoadBuilder tmp2 = RoadBuilder();
	Road A2 = tmp.BuildA2();
	Road A1 = tmp.BuildA1();
	EventManager eventManager = EventManager();

/////////////////////////////////////////////////dodawanie samochod do drogi/////////////////////////////////////////
	for (int j = 0; j< 10; j++)
	{
		eventManager.spawnCar("CAR", 0, 10,A2,"RIGHT");
	}
	for (int j = 0; j< 10; j++)
	{
		eventManager.spawnCar("CAR", 0, 10, A1, "RIGHT");
	}
	for (int j = 0; j< 10; j++)
	{
		eventManager.spawnCar("CAR", 0, 10, A2, "LEFT");
	}
	for (int j = 0; j< 10; j++)
	{
		eventManager.spawnCar("CAR", 0, 10, A1, "LEFT");
	}
	
	while (true)
	{
		//////////////////////////////////////////////iterator pasow (przygotowane dla domyslnie jedenego pasa)//////////////////////////////////////////////////////////
		bool bl = false;
		
		for (std::vector<RoadLine>::iterator it = A2.rightLines.begin(); it != A2.rightLines.end(); it++)
		{//zmienne samochodu do przeniesienia na inna liste(najlepiej byloby zamienic to na obiekt RoadEvent
			int a = 0;
			int lenght_ = 0;
			///////////////////////////////////////////////iterator eventow na pasie/////////////////////////////////////////////////
			for (std::vector<RoadEvent>::iterator itt = (*it).Event.begin(); itt != (*it).Event.end(); itt++)
			{
				int direction = Tool.RandF(0, 1);   //pozniej tutaj funkcja sterujaca zachowaniem samochodow na skrzyzowaniu
				direction = 1;						//do testowania
				if ((*itt).name == "CAR")
				{
					auto tmp = std::next(itt, 1);
					RoadEvent nextEvent = *tmp;
					RoadEvent currentEvent = *itt;
					///////////////////////////////////////////jazda prosto z pierwszenstwem//// pozniej zamienic to w funkcje////////////////////////////////////////////////////////////////////////////
					if ( Tool.getDistance((*itt), nextEvent)+(*itt).curentSpeed >=2 )
					{
						bool cross = false;
						if(direction == 1 && nextEvent.name == "CROSS")
						{

							tmp = std::next(itt, 2);
							nextEvent = *tmp;
							cross = true;
						}
						if (Tool.getDistance(currentEvent, nextEvent) > 0 )
						{
							if (Tool.getDistance(currentEvent, nextEvent) + (*itt).curentSpeed > (*itt).safeDistance)

							{
								if ((*itt).curentSpeed < (*itt).topSpeed)
								{
									(*itt).curentSpeed+=(*itt).currentAcc;
								}
							}
							else if ((*itt).curentSpeed > 0)
							{
								int a = 0;
								//(*itt).curentSpeed -= (*itt).currentAcc;
								if((*itt).curentSpeed<0)
								{
								(*itt).curentSpeed = 0;
								}
							}

							if ((*itt).position + (*itt).lenght + (*itt).curentSpeed + 2 > nextEvent.position)
							{
								(*itt).curentSpeed = 0;
							}
							if (Tool.getDistance(currentEvent, nextEvent) + (*itt).curentSpeed > 1 && (*itt).position + (*itt).lenght + (*itt).curentSpeed + 2 > nextEvent.position)

							{
								(*itt).curentSpeed = 2;
							}
							(*itt).Drive((*itt).curentSpeed);
							if (cross == true && (*itt).position+(*itt).curentSpeed>=(*std::next(itt, 1)).position)
							{
								iter_swap(itt, std::next(itt, 1));
								cross = false;
							}
						}
							
					}
					////////////////////////////////////////////logika skretu w lewo///////// jesli sie da zapakowac do fukcji///////////////
					if (nextEvent.name == "CROSS" && Tool.getDistance((*itt), nextEvent)+(*itt).curentSpeed < 15 && direction == 0)
					{
					///////iterator po drodze w ktora skreca samochod//////////////////////////
						for (std::vector<RoadLine>::iterator ol = A1.rightLines.begin(); ol != A1.rightLines.end(); ol++)
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
									if ((prevEvent.position + prevEvent.lenght + prevEvent.curentSpeed + 3
										> (*oll).position && Tool.getDistance((*oll), nextEvent1) < (10 + (*itt).lenght + (*itt).curentSpeed + (*itt).safeDistance))
										&&(Tool.turnLeftPrediction((*itt),nextEvent,prevEvent,(*oll))==true))
									{
										(*itt).curentSpeed = 0;
									}
									else
									{
										bl = true;
										a = (*oll).position + std::abs((nextEvent.position - (*itt).position + (*itt).lenght) - (*itt).curentSpeed);
										lenght_ = (*itt).lenght;
										itt = (*it).Event.erase(itt);
									}
								}
							}
						}
					}
				
				}
				
			}
			(*it).RoadLinePrint(ConsolColor::RED);
			/////////////////////////////dalej logika skretu w lewo///// dodanie samochodu do innej drogi/////////////////////////////////////////////////
			if (bl == true)
			{
				eventManager.insertCar("CAR", a, lenght_, A1, "RIGHT");
			}
			bl = false;
		}
		///////////////////////////////////////lewy pas EASTROAD//////////////////////////////////////////////////////////////////
		/////////////////////////////////////	iterator pasow /////////////////////////////////////////////////
		bool b2 = false; 
	
		for (std::vector<RoadLine>::iterator it = A2.leftLines.begin(); it != A2.leftLines.end(); it++)
		{
			int a = 0;
			int lenght_ = 0;

			
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
						for (std::vector<RoadLine>::iterator ol = A1.leftLines.begin(); ol != A1.leftLines.end(); ol++)
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
					
				}

			}
			//(*it).RoadLinePrint(ConsolColor::BLUE);
			/////////////////////////////dalej logika skretu w prawo///// dodanie samochodu do innej drogi/////////////////////////////////////////////////
			if (b2 == true)
			{
				
				eventManager.insertCar("CAR", a, lenght_, A1, "LEFT");
			

			}
			b2 = false;
		
		
		}
		
		for (std::vector<RoadLine>::iterator tu = A1.rightLines.begin(); tu != A1.rightLines.end(); tu++)
		{
			
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
					
					
				}
				
				
			}
			//(*tu).RoadLinePrint(ConsolColor::YELLOW);
			

		}
	}
	
	
	
}

Simulation::~Simulation()
{
}
