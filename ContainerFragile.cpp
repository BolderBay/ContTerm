#include "ContainerFragile.h"

ContainerFragile::ContainerFragile() {
	company = "NONE";
	number = 0;
	length = width = height = 1;
	cost = 1;
	mass = 1;
	maxmass = 1;
}

ContainerFragile::ContainerFragile(std::string comp, unsigned int num, unsigned int l, unsigned int w, unsigned int h, float cst, float ms, float mxm) {
	if (comp.size() == 0) throw std::exception("Empty company name\n");
	if (num == 0 or l == 0 or w == 0 or h == 0 or cst == 0 or ms == 0 or mxm == 0) throw std::exception("Zero parameter\n");
	company = comp;
	number = num;
	length = l;
	width = w;
	height = h;
	cost = cst;
	mass = ms;
	maxmass = mxm;
}

void ContainerFragile::printInfo() {
	std::cout << "Company: " << company << ", dimensions (l,w,h): (" << length << "," << width << "," << height << "), cost: " << cost << ", weight:" << mass << ", max weight: " << maxmass << std::endl;
}

std::string ContainerFragile::returnType() {
	return "ContainerFragile";
}


