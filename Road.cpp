#include "Road.h"
#include <vector>
#include "RoadLine.h"
#include "RoadEvent.h"
#include "Tools.h"
#include <string>



Road::Road(std::vector<RoadLine>& rightLines, std::vector<RoadLine>& leftLines)
{
	this->rightLines = rightLines;
	this->leftLines = leftLines;

	
}


Road::~Road()
{
}
