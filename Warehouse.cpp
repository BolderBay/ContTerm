#include "Warehouse.h"

Warehouse::Warehouse()
{
	containersNumber = 0;
	length = 5;
	width = 5;
	height = 5;
	temperature = 0.0;

}

Warehouse::Warehouse(unsigned int l, unsigned int w, unsigned int h, float t) {
	containersNumber = 0;
	length = l;
	width = w;
	height = h;
	temperature = t;
}
std::string Warehouse::getType(unsigned int num) {
	if (containers.count(num) >= 1) {
		if (ContainerCold* p = dynamic_cast<ContainerCold*>(containers[num])) { return p->returnType(); }
		if (ContainerFragile* p = dynamic_cast<ContainerFragile*>(containers[num])) { return p->returnType(); }
		if (ContainerFC* p = dynamic_cast<ContainerFC*>(containers[num])) { return p->returnType(); }
		return containers[num]->returnType();
	}
	else throw std::exception("Incorrect number\n");
}

void Warehouse::addContainer(Container& cont, Coordinatios coord) {
	containers.insert(pair<unsigned int, Container*>(cont.getNumber(), &cont));

}

float Warehouse::getTemp(unsigned int num) {
	if (ContainerCold* p = dynamic_cast<ContainerCold*>(containers[num])) { return p->getTemp();}
	else {throw std::exception("This is not a refrigerated container \n"); }
	
}