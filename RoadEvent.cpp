#include "RoadEvent.h"
#include "Road.h"
#include <iostream>






RoadEvent::RoadEvent(std::string name,int position, int lenght, int topSpeed, int currentSpeed, int maxAcc, int currentAcc, int safeDistance)
{
	this->name = name;
	this->position = position;
	this->lenght = lenght;
	this->topSpeed = topSpeed;
	this->curentSpeed = currentSpeed;
	this->maxAcc = maxAcc;
	this->currentAcc = currentAcc;
	this->safeDistance = safeDistance;

}
/*RoadEvent::RoadEvent(std::string name, int position, int lenght, Road &road)
{
	this->name = name;
	this->position = position;
	this->lenght = lenght;
	this->road = road;

}*/

RoadEvent::RoadEvent(std::string name, int position, int lenght)
{
	this->name = name;
	this->position = position;
	this->lenght = lenght;


}
/*RoadEvent::RoadEvent(std::string name, int position, int lenght , Road& road)
{
	this->name = name;
	this->position = position;
	this->lenght = lenght;


}*/

void RoadEvent::Drive(int a) {
	//std::cout << "Jade" << std::endl;
	
	position=position+a;

}

/*void RoadEvent::Drive(Road* road) {
	position++;

}*/
RoadEvent::~RoadEvent()
{
}
