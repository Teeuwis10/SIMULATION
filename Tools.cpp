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

Tools::~Tools()
{
}
