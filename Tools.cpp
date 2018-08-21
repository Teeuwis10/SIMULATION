#include "Tools.h"
#include "ParamHolder.h"
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <vector>
#include <iostream>
#include <chrono>
#include <memory>
#include <random>
#include "RoadEvent.h"

Tools::Tools()
{
}
///////////////return random number///////////////////////////////
int Tools::RandF(int min, int max)
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::uniform_int_distribution<int> di(min, max);
	auto rng = std::default_random_engine(seed);

	return di(rng);
}
int Tools::getDistance(RoadEvent Event1, RoadEvent Event2)
{
	if (Event2.position>Event1.position)
	{
		int a = Event2.position- (Event1.position + Event1.lenght)  ;
		if (a > 0) {
			return a;
		}
		else return 0;
		
		
	}
	else
	{
		int a = Event1.position - (Event2.lenght + Event2.position);
		if (a > 0) {
			return a;
		}
		else return 0;
	}
};
///////////////////////////jesli prawda do zdazy przejechac przed samochodem z naprzeciwka//////////////////////////////////
bool Tools::turnLeftPrediction(RoadEvent goingLeft, RoadEvent goingLeftCross, RoadEvent goingStright, RoadEvent goingStrightCross)
{
	int unitsToGo = goingLeftCross.position - goingLeft.position + 10;
	int unitsToGo1 = goingStrightCross.position - goingStright.position + 10;
	int time1 = 0;
	int time2 = 0;
	int pos =0;
	for (; unitsToGo > pos; time1++)
	{
		pos += goingLeft.curentSpeed;
		
		goingLeft.curentSpeed += goingLeft.currentAcc;
			if(goingLeft.curentSpeed > goingLeft.topSpeed)
			{
				goingLeft.curentSpeed = goingLeft.topSpeed;
			}
	}
	for (; unitsToGo1 > pos; time2++)
	{
		pos += goingStright.curentSpeed;
		
		goingStright.curentSpeed += goingStright.currentAcc;
		if (goingStright.curentSpeed > goingStright.topSpeed)
		{
			goingStright.curentSpeed = goingStright.topSpeed;
		}
	}
	if (time1 < time2)
	{
		return true;
	}
	else return false;
}

Tools::~Tools()
{
}
