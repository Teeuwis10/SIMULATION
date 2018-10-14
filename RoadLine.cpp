#include "RoadLine.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include "RoadEvent.h"
#include <stdlib.h>
#include <iostream>
#include "Tools.h"
#include <iomanip>
#include <iterator>
#include <Windows.h>
#include "ConsolColor.h"
RoadLine::RoadLine(std::string roadName, std::string lineName,std::vector<RoadEvent>& Event) {

	this->Event = Event;
	this->roadName = roadName;
	this->lineName = lineName;
}

void RoadLine::RoadLinePrint(ConsolColor Color)
{	
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	switch (Color)
	{
	case::ConsolColor::GREEN:
		SetConsoleTextAttribute(hConsole, 10);
		break;
	case::ConsolColor::RED:
		SetConsoleTextAttribute(hConsole, 12);
		break;
	case::ConsolColor::BLUE:
		SetConsoleTextAttribute(hConsole, 9);
		break;
	case::ConsolColor::YELLOW:
		SetConsoleTextAttribute(hConsole, 14);
		break;
	case::ConsolColor::WHITE:
		SetConsoleTextAttribute(hConsole, 15);
		break;
	}
	std::vector<RoadEvent>::iterator itt = Event.end();
	itt--;
	int lenght = (*itt).position+1;
	Tools Tool = Tools();
	float density = 0;
	int flow = 0;
	std::cout << "-----------------------------------"<<roadName<<"---"<< lineName<<"----------------------------------------------------" << std::endl;
	std::cout << std::setw(10) << "iterator" << std::setw(20) << "current event" << std::setw(20) << "distance to next" << std::setw(5) << "speed" << std::setw(5) << "acc" << std::setw(5) <<"lenght"  << std::endl;
	

	std::vector<char> tmp(lenght, '-');

	for (std::vector<RoadEvent>::iterator it = Event.begin(); it != Event.end(); it++)
	{
		density += (*it).lenght;
		flow += (*it).curentSpeed*(*it).lenght;
		if((*it).name == "END")
		{
			density = density / (*it).position;
			auto tmp2 = std::next(it, 0);

			RoadEvent nextEvent = *tmp2;
			int index = std::distance(Event.begin(), it);
			std::cout << std::setw(6) << index << " " << std::setw(5) << (*it).name << std::setw(10) << (*it).position << std::setw(20) << Tool.getDistance((*it), nextEvent)
				<< " " << std::setw(5) << nextEvent.name << std::setw(5) << (*it).curentSpeed << std::setw(5) << (*it).currentAcc << std::setw(5) << (*it).lenght << std::endl;
			std::cout << "------------------------------------density: " << density << "------------------------flow: "<< flow  << std::endl;
		}
		else
		{
			auto tmp2 = std::next(it, 1);

			RoadEvent nextEvent = *tmp2;
			int index = std::distance(Event.begin(), it);
			std::cout << std::setw(6) << index << " " << std::setw(5)<< (*it).name << std::setw(10) << (*it).position << std::setw(20) << Tool.getDistance((*it), nextEvent)
				<< " " << std::setw(5) << nextEvent.name << std::setw(5) << (*it).curentSpeed << std::setw(5) << (*it).currentAcc << std::setw(5) << (*it).lenght <<   std::endl;
		}
		
		if((*it).name=="CAR")
		{
			
			for (int i = 0; i < (*it).lenght; i++) {
				if ((*it).position + i > lenght)
				{
					tmp[(*it).lenght] = '>';
				}
				else
				{
					tmp[(*it).position + i] = '>';
				}
			}
		}
		if ((*it).name == "START")
		{
			tmp[(*it).position] = 'S';
			
		}
		if ((*it).name == "END")
		{
			tmp[(*it).position] = 'E';
		}
		if ((*it).name == "CROSS")
		{
			tmp[(*it).position] = 'C';
		}
	}

	for (int i = 0; i < lenght; i++)
	{
		std::cout << tmp[i];
	}
	
	std::cout << std::endl;
	
		SetConsoleTextAttribute(hConsole, 15);
	//	system("pause");
		std::cout << "\033[2J\033[1;1H";
};

RoadLine::~RoadLine()
{
}
