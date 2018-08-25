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
		bool b5 = false;
		/////////////////////////////////////////////prawy pas A2 ////////////////////////////////////////////////////////////////////
		for (std::vector<RoadLine>::iterator it = A2.rightLines.begin(); it != A2.rightLines.end(); it++)
		{//zmienne samochodu do przeniesienia na inna liste(najlepiej byloby zamienic to na obiekt RoadEvent
			int a = 0;
			int lenght_ = 0;
			///////////////////////////////////////////////iterator eventow na pasie/////////////////////////////////////////////////
			for (std::vector<RoadEvent>::iterator itt = (*it).Event.begin(); itt != (*it).Event.end(); itt++)
			{
				int direction = Tool.RandF(0, 2);   //pozniej tutaj funkcja sterujaca zachowaniem samochodow na skrzyzowaniu // 
													// 0 - prosto z pierszenswtwem
													// 1 - skret w lewo
													// 2 - w prawo
				direction = 2;						//do testowania
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
							else if ((*itt).curentSpeed > 6)
							{
								int a = 0;
								//(*itt).curentSpeed -= (*itt).currentAcc;
								(*itt).curentSpeed -= 2;
								if((*itt).curentSpeed<0)
								{
								(*itt).curentSpeed = 0;
								}
							}

							if ((*itt).position + (*itt).lenght + (*itt).curentSpeed + 2 > nextEvent.position)
							{
								(*itt).curentSpeed = 0;
							}
							if ((*itt).curentSpeed == 0 && (*itt).position + (*itt).lenght + (*itt).curentSpeed + 3 < nextEvent.position)

							{
								(*itt).curentSpeed = 6;
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
					if (nextEvent.name == "CROSS" && currentEvent.position+currentEvent.lenght+(*itt).curentSpeed + 10 > nextEvent.position && direction == 0)
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
									
									
									if (((prevEvent.position + prevEvent.lenght + prevEvent.curentSpeed + 3 >(*oll).position && (Tool.getDistance((*oll), nextEvent1))
										> (10 + (*itt).lenght + (*itt).curentSpeed + (*itt).safeDistance))))
									{
										for (std::vector<RoadLine>::iterator jk = A2.leftLines.begin(); jk != A2.leftLines.end(); jk++)
										{
											for (std::vector<RoadEvent>::iterator jkk = (*jk).Event.begin(); jkk != (*jk).Event.end(); jkk++)
											{
												if ((*jkk).name == "CROSS")
												{
													/*if (prevEvent.position + prevEvent.lenght + prevEvent.curentSpeed + 3 > (*jkk).position)
													{
														std::cout << "dzialam 1" << std::endl;
													}

													if (Tool.getDistance((*oll), nextEvent1) < (10 + (*itt).lenght + (*itt).curentSpeed + (*itt).safeDistance))
													{
														std::cout << "dzialam 2" << std::endl;
													}

													if (Tool.turnLeftPrediction((*itt), nextEvent, prevEvent, (*oll)) == false)
													{
														std::cout << "dzialam 3" << std::endl;
													}*/
													auto tmpin = std::next(jkk, -1);
													auto tmp2in = std::next(jkk, 1);
													RoadEvent prevEventin = *tmpin;
													RoadEvent nextEvent1in = *tmp2in;
													if (Tool.turnLeftPrediction((*itt), nextEvent, prevEventin, (*jkk)) == false)
													{
														std::cout << "nie moge wjechac na: A1 prawy pas" << std::endl;

														(*itt).curentSpeed = 0;
													}
													else
													{
														std::cout << "wjezdzam na: A1 prawy pas" << std::endl;
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
						}
					}
					////////////////////////////////////////////logika skretu w prawo///////////////////////////////////////////////////////////////
					if (nextEvent.name == "CROSS" && Tool.getDistance((*itt), nextEvent) + (*itt).curentSpeed < 15 && direction == 2)       // jedz w lewo
					//if (0>1)       // jedz w lewo
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
										&& (Tool.turnLeftPrediction((*itt), nextEvent, prevEvent, (*oll)) == false)
										)
									{
										(*itt).curentSpeed = 0;
										std::cout << "nie moge wjechac na: A1 lewy pas" << std::endl;

									}
									else
									{
										
										std::cout << "wjezdzam na: A1 lewy pas" << std::endl;
										b5 = true;
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
			if (b5 == true)
			{
				eventManager.insertCar("CAR", a, lenght_, A1, "LEFT");
			}
			b5 == false;
			bl = false;
		}
		//////////////////////////////////////////////iterator pasow (przygotowane dla domyslnie jedenego pasa)//////////////////////////////////////////////////////////
		bool b3 = false;
		/////////////////////////////////////////////prawy pas A1////////////////////////////////////////////////////
		for (std::vector<RoadLine>::iterator it = A1.rightLines.begin(); it != A1.rightLines.end(); it++)
		{//zmienne samochodu do przeniesienia na inna liste(najlepiej byloby zamienic to na obiekt RoadEvent
			int a = 0;
			int lenght_ = 0;
			///////////////////////////////////////////////iterator eventow na pasie/////////////////////////////////////////////////
			for (std::vector<RoadEvent>::iterator itt = (*it).Event.begin(); itt != (*it).Event.end(); itt++)
			{
				int direction = Tool.RandF(0, 1);   //pozniej tutaj funkcja sterujaca zachowaniem samochodow na skrzyzowaniu // 
													// 0 - prosto z pierszenswtwem
													// 1 - skret w lewo
			//	direction = 1;						//do testowania
				if ((*itt).name == "CAR")
				{




					auto tmp = std::next(itt, 1);
					RoadEvent nextEvent = *tmp;
					RoadEvent currentEvent = *itt;
					///////////////////////////////////////////jazda prosto z pierwszenstwem//// pozniej zamienic to w funkcje////////////////////////////////////////////////////////////////////////////
					if (Tool.getDistance((*itt), nextEvent) + (*itt).curentSpeed >= 2)
					{
						bool cross = false;
						if (direction == 1 && nextEvent.name == "CROSS")
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
								}
							}
							else if ((*itt).curentSpeed > 6)
							{
								int a = 0;
								//(*itt).curentSpeed -= (*itt).currentAcc;
								(*itt).curentSpeed -= 2;
								if ((*itt).curentSpeed<0)
								{
									(*itt).curentSpeed = 0;
								}
							}

							if ((*itt).position + (*itt).lenght + (*itt).curentSpeed + 2 > nextEvent.position)
							{
								(*itt).curentSpeed = 0;
							}
							if ((*itt).curentSpeed == 0 && (*itt).position + (*itt).lenght + (*itt).curentSpeed + 3 < nextEvent.position)

							{
								(*itt).curentSpeed = 6;
							}
							(*itt).Drive((*itt).curentSpeed);
							if (cross == true && (*itt).position + (*itt).curentSpeed >= (*std::next(itt, 1)).position)
							{
								iter_swap(itt, std::next(itt, 1));
								cross = false;
							}
						}

					}
					////////////////////////////////////////////logika skretu w lewo///////// jesli sie da zapakowac do fukcji///////////////
					if (nextEvent.name == "CROSS" && currentEvent.position + currentEvent.lenght + (*itt).curentSpeed + 10 > nextEvent.position && direction == 0)
					{

						///////iterator po drodze w ktora skreca samochod//////////////////////////
						for (std::vector<RoadLine>::iterator ol = A2.leftLines.begin(); ol != A2.leftLines.end(); ol++)
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
										&& (Tool.turnLeftPrediction((*itt), nextEvent, prevEvent, (*oll)) == true))
									{
										std::cout << "nie moge wjechac" << std::endl;
										(*itt).curentSpeed = 0;
									}

									if ((*itt).position + (*itt).lenght + (*itt).curentSpeed > (*oll).position)
									{
										b3 = true;
										a = (*oll).position + std::abs((nextEvent.position - (*itt).position + (*itt).lenght) - (*itt).curentSpeed);
										lenght_ = (*itt).lenght;
										itt = (*it).Event.erase(itt);
									}
									else
									{
										int a = (*itt).curentSpeed + (*itt).currentAcc;
										if (a > (*itt).topSpeed) {
											(*itt).curentSpeed = (*itt).topSpeed;
										}
										(*itt).Drive((*itt).curentSpeed);
									}
								}
							}
						}
					}

				}

			}
			//(*it).RoadLinePrint(ConsolColor::GREEN);
			/////////////////////////////dalej logika skretu w lewo///// dodanie samochodu do innej drogi/////////////////////////////////////////////////
			if (b3 == true)
			{
				eventManager.insertCar("CAR", a, lenght_, A1, "RIGHT");
			}
			b3 = false;
		}
		///////////////////////////////////////lewy pas A2//////////////////////////////////////////////////////////////////
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
				// direction = 1;
				if ((*itt).name == "CAR")

				{
					
					auto tmp = std::next(itt, 1);
					RoadEvent nextEvent = *tmp;
					RoadEvent currentEvent = *itt;
					///////////////////////////////////////////jazda prosto z pierwszenstwem//// pozniej zamienic to w funkcje////////////////////////////////////////////////////////////////////////////
					if (Tool.getDistance((*itt), nextEvent) + (*itt).curentSpeed >= 2)
					{
						bool cross = false;
						if (direction == 1 && nextEvent.name == "CROSS")
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
								}
							}
							else if ((*itt).curentSpeed > 6)
							{
								int a = 0;
								//(*itt).curentSpeed -= (*itt).currentAcc;
								(*itt).curentSpeed -= 2;
								if ((*itt).curentSpeed<0)
								{
									(*itt).curentSpeed = 0;
								}
							}

							if ((*itt).position + (*itt).lenght + (*itt).curentSpeed + 2 > nextEvent.position)
							{
								(*itt).curentSpeed = 0;
							}
							if ((*itt).curentSpeed == 0 && (*itt).position + (*itt).lenght + (*itt).curentSpeed + 3 < nextEvent.position)

							{
								(*itt).curentSpeed = 6;
							}
							(*itt).Drive((*itt).curentSpeed);
							if (cross == true && (*itt).position + (*itt).curentSpeed >= (*std::next(itt, 1)).position)
							{
								iter_swap(itt, std::next(itt, 1));
								cross = false;
							}
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
					
					//auto index = std::distance((*it).Event.begin(), itt);
					
				}

			}
			
			/////////////////////////////dalej logika skretu w prawo///// dodanie samochodu do innej drogi/////////////////////////////////////////////////
			if (b2 == true)
			{
				
				eventManager.insertCar("CAR", a, lenght_, A1, "LEFT");
			

			}
			b2 = false;
			(*it).RoadLinePrint(ConsolColor::BLUE);
		
		}
		///////////////////////////////////////lewy pas A1//////////////////////////////////////////////////////////////////
		/////////////////////////////////////	iterator pasow /////////////////////////////////////////////////
		 bool b8 = false;

		for (std::vector<RoadLine>::iterator it = A1.leftLines.begin(); it != A1.leftLines.end(); it++)
		{
			int a = 0;
			int lenght_ = 0;


			///////////////////////////////////////////////iterator eventow na pasie/////////////////////////////////////////////////
			for (std::vector<RoadEvent>::iterator itt = (*it).Event.begin(); itt != (*it).Event.end(); itt++)
			{

				int direction = Tool.RandF(0, 1);
				 //direction = 1;
				if ((*itt).name == "CAR")

				{

					auto tmp = std::next(itt, 1);
					RoadEvent nextEvent = *tmp;
					RoadEvent currentEvent = *itt;
					///////////////////////////////////////////jazda prosto z pierwszenstwem//// pozniej zamienic to w funkcje////////////////////////////////////////////////////////////////////////////
					if (Tool.getDistance((*itt), nextEvent) + (*itt).curentSpeed >= 2)
					{
						bool cross = false;
						if (direction == 1 && nextEvent.name == "CROSS")
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
								}
							}
							else if ((*itt).curentSpeed > 6)
							{
								int a = 0;
								//(*itt).curentSpeed -= (*itt).currentAcc;
								(*itt).curentSpeed -= 2;
								if ((*itt).curentSpeed<0)
								{
									(*itt).curentSpeed = 0;
								}
							}

							if ((*itt).position + (*itt).lenght + (*itt).curentSpeed + 2 > nextEvent.position)
							{
								(*itt).curentSpeed = 0;
							}
							if ((*itt).curentSpeed == 0 && (*itt).position + (*itt).lenght + (*itt).curentSpeed + 3 < nextEvent.position)

							{
								(*itt).curentSpeed = 6;
							}
							(*itt).Drive((*itt).curentSpeed);
							if (cross == true && (*itt).position + (*itt).curentSpeed >= (*std::next(itt, 1)).position)
							{
								iter_swap(itt, std::next(itt, 1));
								cross = false;
							}
						}

					}

					////////////////////////////////////////////logika skretu w lewo///////////////////////////////////////////////////////////////
					if (nextEvent.name == "CROSS" && Tool.getDistance((*itt), nextEvent) + (*itt).curentSpeed < 15 && direction == 0)       // jedz w lewo
					{

						///////iterator po drodze w ktora skreca samochod//////////////////////////
						for (std::vector<RoadLine>::iterator ol = A2.rightLines.begin(); ol != A2.rightLines.end(); ol++)
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
										&& (Tool.turnLeftPrediction((*itt), nextEvent, prevEvent, (*oll)) == false)
										)
									{
										(*itt).curentSpeed = 0;

									}
									else
									{
										b8 = true;
										a = (*oll).position + std::abs((nextEvent.position - (*itt).position + (*itt).lenght) - (*itt).curentSpeed);
										lenght_ = (*oll).lenght;
										itt = (*it).Event.erase(itt);

									}

								}
							}

						}
					}

				//	auto index = std::distance((*it).Event.begin(), itt);

				}

			}

			/////////////////////////////dalej logika skretu w prawo///// dodanie samochodu do innej drogi/////////////////////////////////////////////////
			if (b8 == true)
			{

				eventManager.insertCar("CAR", a, lenght_, A2, "RIGHT");


			}
			b8 = false;
			(*it).RoadLinePrint(ConsolColor::YELLOW);

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
