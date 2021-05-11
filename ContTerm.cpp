#include "Terminal.h"

#include <iostream>
#include <iomanip>


int main() {
	Container cont;
	ContainerCold cold;
	ContainerFragile fra;
	ContainerFC fc;
	cont.printInfo();
	cold.printInfo();
	fra.printInfo();
	fc.printInfo();
}