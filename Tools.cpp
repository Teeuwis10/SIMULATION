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
Tools::~Tools()
{
}
