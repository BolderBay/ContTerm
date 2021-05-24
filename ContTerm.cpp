#include "Terminal.h"

#include <iostream>
#include <iomanip>


int main() {
	
	Container container1("US", 322, 2, 1, 0, 500, 100);
	Container container2("EU", 226, 2, 1, 0, 500, 100);
	Container container3("RU", 431, 2, 2, 0, 500, 100);
	Container test("test", 555, 1, 1, 1, 500, 100);

	Coordinatios pos1(0, 0, 0, FRONT);
	Coordinatios pos2(1, 2, 0, SIDE);
	Coordinatios pos3(3, 3, 0, FRONT);
	
	Coordinatios testpos(0, 2, 0, FRONT);

	Warehouse sklad;

	sklad.addContainer(container1, pos1);
	sklad.addContainer(container2, pos2);
	sklad.addContainer(container3, pos3);

	cout << sklad.checkPlace(test, testpos);

	sklad.showSheme();


}