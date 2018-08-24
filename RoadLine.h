#pragma once
#include "RoadEvent.h"
#include <vector>
#include <iostream>
#include "ConsolColor.h"
class RoadLine
{
public:
	std::vector<RoadEvent> Event;
	std::string roadName;
	std::string lineName;
	

	RoadLine(std::string roadName,std::string roadline, std::vector<RoadEvent>& Event);
	void RoadLinePrint(ConsolColor Color);
	~RoadLine();
	
	
};

