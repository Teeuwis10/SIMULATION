
#include "ParamHolder.h"
#include "Simulation.h"
#include <iostream>
int main()
{
	ParamHolder Paramiters = ParamHolder();

	Simulation simulation = Simulation();
	simulation.StartSimulation(Paramiters);




	system("pause");




	return 0;
}