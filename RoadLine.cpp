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
RoadLine::RoadLine(std::vector<RoadEvent>& Event) {

	this->Event = Event;
}

void RoadLine::RoadLinePrint()
{
	std::vector<RoadEvent>::iterator itt = Event.end();
	itt--;
	int lenght = (*itt).position+1;
	Tools Tool = Tools();
	
	//int * tmp = new int[lenght];
	//std::fill_n(tmp, lenght, 0);

	std::vector<char> tmp(lenght, '-');

	for (std::vector<RoadEvent>::iterator it = Event.begin(); it != Event.end(); it++)
	{
		if((*it).name == "END")
		{
			auto tmp2 = std::next(it, 0);

			RoadEvent nextEvent = *tmp2;
			int index = std::distance(Event.begin(), it);
			std::cout << std::setw(10) << index << std::setw(20) << (*it).position << std::setw(20) << (*it).lenght << " " << (*it).name << std::setw(20) << Tool.getDistance((*it), nextEvent) << " " << nextEvent.name << std::endl;
		}
		else
		{
			auto tmp2 = std::next(it, 1);

			RoadEvent nextEvent = *tmp2;
			int index = std::distance(Event.begin(), it);
			std::cout << std::setw(10) << index << std::setw(20) << (*it).position << std::setw(20) << (*it).lenght << " " << (*it).name << std::setw(20) << Tool.getDistance((*it), nextEvent) << " " << nextEvent.name << std::endl;
		}
		//std::cout <<"rozmiar w roadliene print : "<< index1 << std::endl; 
		//std::cout << "rozmiar w roadliene print : " << index2 << std::endl;
		//int index1 = std::distance((*it).Event.begin(), (*it).Event.end());
		if((*it).name=="CAR")
		{
			//tmp[(*it).position] = '>';
			for (int i = 0; i < (*it).lenght; i++) {
				tmp[(*it).position + i ] = '>';
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
	//	for (std::vector<int>::iterator it = tmp.begin(); it != tmp.end(); it++) {}

	std::cout << std::endl;
	
		
		system("pause");
		std::cout << "\033[2J\033[1;1H";
};

RoadLine::~RoadLine()
{
}
