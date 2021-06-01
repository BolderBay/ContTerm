#include "ContainerFC.h"

ContainerFC::ContainerFC() {
	company = "NONE";
	number = 0;
	length = width = height = 1;
	cost = 1;
	mass = 1;
	maxmass = 5;
	maxtemp = 5;
}

ContainerFC::ContainerFC(std::string comp, unsigned int num, unsigned int l, unsigned int w, unsigned int h, float cst, float ms, float mxt, float mxm) {
	if (comp.size() == 0) throw std::exception("Empty company name\n");
	if (num == 0 or l == 0 or w == 0 or h == 0 or cst == 0 or ms == 0 or mxt == 0 or mxm == 0) throw std::exception("Zero parameter\n");
	company = comp;
	number = num;
	length = l;
	width = w;
	height = h;
	cost = cst;
	mass = ms;
	maxtemp = mxt;
	maxmass = mxm;
}
void ContainerFC::printInfo() {
	std::cout << "Company: " << company << ", dimensions: (" << length << "," << width << "," << height << "), cost: " << cost << ", weight:" << mass << ", max temperature: " << maxtemp << ", max weight: " << maxmass << std::endl;
}

std::string ContainerFC::returnType() {
	return "ContainerFC";
}

std::string ContainerFC::forSave() {
	std::string data = company + " " + std::to_string(number) + " " + std::to_string(length) + " " + std::to_string(width) + " " +
		std::to_string(height) + " " + std::to_string(cost) + " " + std::to_string(mass) + " " + std::to_string(maxtemp) + " " + std::to_string(maxmass);
	return data;
}
