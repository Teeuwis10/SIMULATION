#include "RoadEvent.h"




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
	brokenline
		brokenline2
}
RoadEvent::RoadEvent(std::string name, int position, int lenght)
{
	this->name = name;
	this->position = position;
	this->lenght = lenght;
	this->topSpeed = topSpeed;
}

void RoadEvent::Drive() {
	position++;
}
RoadEvent::~RoadEvent()
{
}
