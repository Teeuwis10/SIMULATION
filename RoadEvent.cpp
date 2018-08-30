#include "RoadEvent.h"
#include "Road.h"
#include <iostream>
#include <utility>
#include <vector>
RoadEvent::RoadEvent(std::string name,int position, int lenght, int topSpeed, int currentSpeed, int maxAcc, int currentAcc, int safeDistance,int direction, std::string spawnlane)
{
	this->name = name;
	this->position = position;
	this->lenght = lenght;
	this->topSpeed = topSpeed;
	this->curentSpeed = currentSpeed;
	this->maxAcc = maxAcc;
	this->currentAcc = currentAcc;
	this->safeDistance = safeDistance;
	this->direction = direction;
	this->spawnLane = spawnLane;

}

RoadEvent::RoadEvent(std::string name, int position, int lenght)
{
	this->name = name;
	this->position = position;
	this->lenght = lenght;
	this->topSpeed = 0;
	this->curentSpeed = 0;
	this->maxAcc = 0;
	this->currentAcc = 0;
	this->safeDistance = 0;

}
RoadEvent::RoadEvent(){}

void RoadEvent::Drive(int a) {
	
	position=position+a;
}

RoadEvent::~RoadEvent()
{
}
