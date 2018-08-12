#pragma once
#include <vector>
#include "RoadLine.h"
#include "Road.h"
#include <string>
class Road
{
	
public:
	

	std::vector<RoadLine> rightLines;
	std::vector<RoadLine> leftLines;

	//void spawnCar( int position, int lenght);
	//Road(vector<RoadLine> &rightLines, vector<RoadLine> &leftLines);
	Road(std::vector<RoadLine>& rightLines, std::vector<RoadLine>& leftLines);
	
	
	~Road();
};
