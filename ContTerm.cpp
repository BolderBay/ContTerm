#include "Terminal.h"

#include <iostream>
#include <iomanip>


int main() {
	Container cont;
	ContainerCold cold;
	ContainerFragile fra;
	ContainerFC fc;

	cold.setNumber(1);
	fra.setNumber(2);
	fc.setNumber(3);

	Warehouse sklad;

	Coordinatios p;
	p.x = 1;
	p.y = 1;
	p.z = 1;
	p.orientation = 1;

	sklad.addContainer(cont, p);
	sklad.addContainer(cold, p);
	sklad.addContainer(fra, p);
	sklad.addContainer(fc, p);

	for (int i = 0; i < 5; ++i) {
		try {
			cout << sklad.getType(i) << endl;
			cout << sklad.getTemp(i) << endl;
		}
		catch (std::exception& error) { cout << error.what(); }
	}

}