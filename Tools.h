#pragma once
#include "RoadEvent.h"
class Tools
{
public:
	Tools();
	int RandF(int min, int max);
	int getDistance(RoadEvent Event1, RoadEvent Event2);
	~Tools();
};

