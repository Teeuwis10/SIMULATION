#include "Road.h"
#include <vector>
#include "RoadLine.h"
#include "RoadEvent.h"
#include "Tools.h"
#include <string>



Road::Road(std::string name, std::vector<RoadLine>& rightLines, std::vector<RoadLine>& leftLines)
{
	this->rightLines = rightLines;
	this->leftLines = leftLines;
	this->name = name;

	
}


Road::~Road()
{
}
