#pragma once
#include <string>
//#include "Road.h"
//#include "RoadLine.h"
//#include "EventManager.h"
//#include "Tools.h"



class RoadEvent
{
public:
	//std::vector<RoadLine>  road;
	std::string name;
	int position;
	int lenght;
	int topSpeed;
	int curentSpeed;
	int maxAcc;
	int currentAcc;
	int safeDistance;
	

	RoadEvent(std::string name, int position, int lenght, int topSpeed, int currentSpeed, int maxAcc, int currentAcc, int safeDistance);
	RoadEvent(std::string name, int position, int lenght);
	//RoadEvent(std::string name, int position, int lenght, Road& road);
	//void Drive(Road* road);
	void Drive();
	~RoadEvent();
};

