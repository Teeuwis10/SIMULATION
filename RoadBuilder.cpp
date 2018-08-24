#include "RoadBuilder.h"
#include "Tools.h"
#include "RoadLine.h"
#include "RoadEvent.h"
#include "Road.h"
#include <vector>



RoadBuilder::RoadBuilder()
{
}


RoadBuilder::~RoadBuilder()
{
}
Road RoadBuilder::BuildA2()
{	//----------------------------A2----------------------------------------------------------------
	Tools rand = Tools();
	std::vector<RoadLine> rightLines;
	std::vector<RoadLine> leftLines;
	//--------------------------Right Side----------------------------------------------------------
	std::vector<RoadEvent> firstRightLineEvents;

	firstRightLineEvents.push_back(RoadEvent("START",0, 0));
	firstRightLineEvents.push_back(RoadEvent("CROSS", 500, 0));
	firstRightLineEvents.push_back(RoadEvent("END", 999, 0));
	
	rightLines.push_back(RoadLine("A2", "RIGHT 1", firstRightLineEvents));

	//----------------------------Left Side------------------------------------------------------------

	std::vector<RoadEvent> firstLeftLineEvents;

	firstLeftLineEvents.push_back(RoadEvent("START",0, 0));
	firstLeftLineEvents.push_back(RoadEvent("CROSS",500, 0));
	firstLeftLineEvents.push_back(RoadEvent("END", 999, 0));


	leftLines.push_back(RoadLine("A2","LEFT 1", firstLeftLineEvents));
	//------------------Creating Road------------------------------------
	Road Road_ = Road("A2",rightLines, leftLines);
	
	return (Road_);
}
Road RoadBuilder::BuildA1()
{
	Tools rand = Tools();
	std::vector<RoadLine> rightLines;
	std::vector<RoadLine> leftLines;
	//--------------------------Right Side----------------------------------------------------------
	std::vector<RoadEvent> firstRightLineEvents;

	firstRightLineEvents.push_back(RoadEvent("START", 0, 0));
	firstRightLineEvents.push_back(RoadEvent("CROSS", 500, 0));
	firstRightLineEvents.push_back(RoadEvent("END", 999, 0));

	rightLines.push_back(RoadLine("A1","RIGHT 1", firstRightLineEvents));

	//----------------------------Left Side------------------------------------------------------------

	std::vector<RoadEvent> firstLeftLineEvents;

	firstLeftLineEvents.push_back(RoadEvent("START", 0, 0));
	firstLeftLineEvents.push_back(RoadEvent("CROSS", 500, 0));
	firstLeftLineEvents.push_back(RoadEvent("END", 999, 0));


	leftLines.push_back(RoadLine("A1", "LEFT 1", firstLeftLineEvents));
	//------------------Creating Road------------------------------------
	Road Road_ = Road("A1",rightLines, leftLines);
	
	return (Road_);
}