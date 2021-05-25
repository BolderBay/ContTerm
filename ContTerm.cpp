#include "Terminal.h"

#include <iostream>
#include <iomanip>


int main() {
	
	Container container1("US", 322, 2, 1, 1, 500, 100);
	Container container2("EU", 226, 2, 1, 1, 500, 100);
	ContainerFragile container3("RU", 431, 2, 2, 1, 500, 100, 20);
	Container test("test", 555, 1, 2, 1, 500, 100);

	Coordinatios pos1(0, 0, 0, FRONT);
	Coordinatios pos2(1, 2, 0, SIDE);
	Coordinatios pos3(3, 3, 0, FRONT);
	Coordinatios pos4(0, 0, 1, FRONT);
	
	Coordinatios testpos(5, 0, 1, FRONT);

	Warehouse sklad;

	sklad.addContainer(container1, pos1);
	sklad.addContainer(container2, pos2);
	sklad.addContainer(container3, pos3);

	sklad.showSheme(0);



	


}