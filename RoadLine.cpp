#include "RoadLine.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include "RoadEvent.h"
#include <stdlib.h>
#include <iostream>

RoadLine::RoadLine(std::vector<RoadEvent>& Event) {

	this->Event = Event;
}

void RoadLine::RoadLinePrint()
{
	std::vector<RoadEvent>::iterator itt = Event.end();
	itt--;
	int lenght = (*itt).position+1;

	//int * tmp = new int[lenght];
	//std::fill_n(tmp, lenght, 0);

	std::vector<char> tmp(lenght, '-');

	for (std::vector<RoadEvent>::iterator it = Event.begin(); it != Event.end(); it++)
	{
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
