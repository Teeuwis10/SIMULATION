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
Road RoadBuilder::BuildEast()
{
	Tools rand = Tools();
	std::vector<RoadLine> rightLines;
	std::vector<RoadLine> leftLines;
	//--------------------------Right Side----------------------------------------------------------
	std::vector<RoadEvent> firstRightLineEvents;

	firstRightLineEvents.push_back(RoadEvent("START",0, 0));
	firstRightLineEvents.push_back(RoadEvent("CROSS", 500, 0));
	firstRightLineEvents.push_back(RoadEvent("END", 999, 0));
	
	rightLines.push_back(RoadLine(firstRightLineEvents));

	//----------------------------Left Side------------------------------------------------------------

	std::vector<RoadEvent> firstLeftLineEvents;

	firstLeftLineEvents.push_back(RoadEvent("START",99, 0));
	firstLeftLineEvents.push_back(RoadEvent("END",0, 0));


	leftLines.push_back(RoadLine(firstLeftLineEvents));
	//------------------Creating Road------------------------------------
	//	Road FirstRoad = Road(rightLines, leftLines);
	//TEST FirstRoad = TEST(10,10);
	Road FirstRoad = Road(rightLines, leftLines);
	//TEST a = TEST(rand.RandF(1,2),rand.RandF(1,2));
	return (FirstRoad);
}
Road RoadBuilder::BuildSouth()
{
	Tools rand = Tools();
	std::vector<RoadLine> rightLines;
	std::vector<RoadLine> leftLines;
	//--------------------------Right Side----------------------------------------------------------
	std::vector<RoadEvent> firstRightLineEvents;

	firstRightLineEvents.push_back(RoadEvent("START", 0, 0));
	firstRightLineEvents.push_back(RoadEvent("CROSS", 500, 0));
	firstRightLineEvents.push_back(RoadEvent("END", 999, 0));

	rightLines.push_back(RoadLine(firstRightLineEvents));

	//----------------------------Left Side------------------------------------------------------------

	std::vector<RoadEvent> firstLeftLineEvents;

	firstLeftLineEvents.push_back(RoadEvent("START", 999, 0));
	firstLeftLineEvents.push_back(RoadEvent("CROSS", 500, 0));
	firstLeftLineEvents.push_back(RoadEvent("END", 0, 0));


	leftLines.push_back(RoadLine(firstLeftLineEvents));
	//------------------Creating Road------------------------------------
	//	Road FirstRoad = Road(rightLines, leftLines);
	//TEST FirstRoad = TEST(10,10);
	Road FirstRoad = Road(rightLines, leftLines);
	//TEST a = TEST(rand.RandF(1,2),rand.RandF(1,2));
	return (FirstRoad);
}