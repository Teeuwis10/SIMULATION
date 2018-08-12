#include "RoadLine.h"
#include <vector>
#include <iostream>
#include "RoadEvent.h"

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
			tmp[(*it).position] = '>';
		}
		if ((*it).name == "START")
		{
			tmp[(*it).position] = 'S';
			
		}
		if ((*it).name == "END")
		{
			tmp[(*it).position] = 'E';
		}
		

	}

	for (int i = 0; i < lenght; i++)
	{
		std::cout << tmp[i];
	}
	//	for (std::vector<int>::iterator it = tmp.begin(); it != tmp.end(); it++) {}

	std::cout << std::endl;
	system("pause");
};

RoadLine::~RoadLine()
{
}
