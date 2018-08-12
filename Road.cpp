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
void Road::spawnCar(std::string name, int position, int lenght) {
	std::vector<RoadEvent>::iterator it;
	it = rightLines.at(0).Event.begin();

	auto rng = Tools();

	rightLines.at(0).Event.insert(it, RoadEvent(name ,position, lenght, rng.RandF(4, 5), 0, rng.RandF(1, 2), 0, rng.RandF(2, 5)));
	//rightLines.at(0).Event.insert(it, RoadEvent(name,position, lenght));

}

Road::~Road()
{
}
