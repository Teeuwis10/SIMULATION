#pragma once
#include <vector>
#include "RoadEvent.h"
class RoadLine
{
public:
	std::vector<RoadEvent> Event;
	

	RoadLine(std::vector<RoadEvent>& Event);

	void RoadLinePrint();
	~RoadLine();
	
	
};

