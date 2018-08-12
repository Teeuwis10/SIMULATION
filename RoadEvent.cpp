#include "RoadEvent.h"
#include "Road.h"






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

void RoadEvent::Drive() {
	position++;

}
//RoadEvent::RoadEvent(Road& road){}
//RoadEvent::RoadEvent(int road) {}
RoadEvent::~RoadEvent()
{
}
