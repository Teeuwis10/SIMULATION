#pragma once
#include "RoadEvent.h"
enum Color { RED, GREEN, BLUE };
class Tools
{
public:
	Tools();
	int RandF(int min, int max);
	int getDistance(RoadEvent Event1, RoadEvent Event2);
	bool turnLeftPrediction(RoadEvent goingLeft, RoadEvent goingLeftCross, RoadEvent goingStright, RoadEvent goingStrightCross);
	void driveStright(RoadEvent &currentCar, RoadEvent &nextCar);
	~Tools();
};

