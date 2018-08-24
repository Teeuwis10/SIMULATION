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
	std::string name;

	//void spawnCar( int position, int lenght);
	//Road(vector<RoadLine> &rightLines, vector<RoadLine> &leftLines);
	Road(std::string name, std::vector<RoadLine>& rightLines, std::vector<RoadLine>& leftLines);
	
	
	~Road();
};

