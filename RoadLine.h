#pragma once
#include "RoadEvent.h"
#include <vector>
class RoadLine
{
public:
	std::vector<RoadEvent> Event;
	

	RoadLine(std::vector<RoadEvent>& Event);

	void RoadLinePrint();
	~RoadLine();
	
	
};

