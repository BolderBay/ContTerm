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


void Warehouse::addContainer(Container& cont, Coordinatios coord) {
	containersNumber++;

}