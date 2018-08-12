#pragma once
#include <string>




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
	//RoadEvent(Road& road);
	//RoadEvent(int road);
	void Drive();
	~RoadEvent();
};

