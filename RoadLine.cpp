#include "RoadLine.h"
#include <vector>
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

std::vector<int> tmp(lenght, 0);

for (std::vector<RoadEvent>::iterator it = Event.begin(); it != Event.end(); it++) {
tmp[(*it).position] = 1;

}

for (int i = 0; i < lenght; i++) {
std::cout << tmp[i];

}
//	for (std::vector<int>::iterator it = tmp.begin(); it != tmp.end(); it++) {}

std::cout << std::endl;
system("pause");
};

RoadLine::~RoadLine()
{
}
