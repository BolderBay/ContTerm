#include "ContainerCold.h"

ContainerCold::ContainerCold() {
	company = "NONE";
	number = 0;
	length = width = height = 1;
	cost = 1;
	mass = 1;
	maxtemp = 1;
}

ContainerCold::ContainerCold(std::string comp, unsigned int num, unsigned int l, unsigned int w, unsigned int h, float cst, float ms, float mxt) {
	if (comp.size() == 0) throw std::exception("Empty company name\n");
	if (num == 0 or l == 0 or w == 0 or h == 0 or cst == 0 or ms == 0 or mxt == 0) throw std::exception("Zero parameter\n");
	company = comp;
	number = num;
	length = l;
	width = w;
	height = h;
	cost = cst;
	mass = ms;
	maxtemp = mxt;
}

void ContainerCold::printInfo() {
	std::cout << "Company: " << company << ", dimensions (l,w,h): (" << length << "," << width << "," << height << "), cost: " << cost << ", weight:" << mass << ", max temperature: " << maxtemp << std::endl;
}
