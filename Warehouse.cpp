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

Warehouse::~Warehouse() {
	map<unsigned int, Container*>::iterator iter_cont = containers.begin();
	map<unsigned int, Coordinatios*>::iterator iter_coord = coorditations.begin();
	while (iter_cont != containers.end()) {
		delete iter_cont->second;
		delete iter_coord->second;
		iter_cont->second = nullptr;
		iter_coord->second = nullptr;
		++iter_cont;
		++iter_coord;
	}
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

void Warehouse::addContainer(Container& cont, Coordinatios& coord) {
	if (checkPlace(cont, coord) == true) {
		if (checkDown(cont, coord) == true) {
			float maxMassDown = chechDownWeight(coord);
			if (ContainerCold* p = dynamic_cast<ContainerCold*>(&cont)) {
				if (p->getTemp() < temperature) throw std::exception("Warehouse temperature is too high\n");
			}
			if (ContainerFC* p = dynamic_cast<ContainerFC*>(&cont)) {
				if (p->getTemp() < temperature) throw std::exception("Warehouse temperature is too high\n");
			}
			if (maxMassDown < cont.getMass()) throw std::exception("The container is too heavy\n");
		}
		else throw std::exception("Can't put the container this way\n");
	}
	else throw std::exception("The container can't be placed on this coordinate \n");
	
	containers.insert(pair<unsigned int, Container*>(cont.getNumber(), &cont));
	coorditations.insert(pair<unsigned int, Coordinatios*>(cont.getNumber(), &coord));
	containersNumber = containers.size();

}

float Warehouse::getTemp(unsigned int num) {
	if (ContainerCold* p = dynamic_cast<ContainerCold*>(containers[num])) { return p->getTemp();}
	else {throw std::exception("This is not a refrigerated container \n"); }
	
}

float Warehouse::getMaxmass(unsigned int num) {
	if (ContainerFragile* p = dynamic_cast<ContainerFragile*>(containers[num])) { return p->getMaxmass(); }
	else { throw std::exception("This is not a refrigerated container \n"); }
}

//bool Warehouse::checkPlace(Container& cont, Coordinatios& coord)  {
//	unsigned int uPoint = 0;
//
//	unsigned int x = coord.x;
//	unsigned int y = coord.y;
//	unsigned int z = coord.z;
//	unsigned int l = cont.retSize('l');
//	unsigned int w = cont.retSize('w');
//	unsigned int h = cont.retSize('h');
//	map<unsigned int, Coordinatios*>::iterator iter_coord = coorditations.begin();
//	map<unsigned int, Container*>::iterator iter_cont = containers.begin();
//	if (coord.orientation == FRONT) {
//		Coordinatios mass[8] = { Coordinatios(x,y,z,FRONT),  Coordinatios(x+l,y,z,FRONT),  Coordinatios(x,y+w,z,FRONT) , Coordinatios(x,y,z+h,FRONT) , 
//			Coordinatios(x+l,y+w,z,FRONT) , Coordinatios(x+l,y,z+h,FRONT) , Coordinatios(x,y+w,z+h,FRONT) , Coordinatios(x+l,y+w,z+h,FRONT) };
//		while (iter_coord != coorditations.end()){
//			unsigned int contX = iter_coord->second->x;
//			unsigned int contY = iter_coord->second->y;
//			unsigned int contZ = iter_coord->second->z;
//			unsigned int contL = iter_cont->second->retSize('l');
//			unsigned int contW = iter_cont->second->retSize('w');
//			unsigned int contH = iter_cont->second->retSize('h');
//			for (int i = 0; i < 8; ++i) {
//				if (iter_coord->second->orientation == FRONT) {
//					if ((contX <= mass[i].x) && (mass[i].x <= contX + contL) && (contY <= mass[i].y) && (mass[i].y <= contY + contW) && (contZ <= mass[i].z) && (mass[i].z <= contZ + contH)) { uPoint++; }
//				}
//				if (iter_coord->second->orientation == SIDE) {
//					if ((contX <= mass[i].x) && (mass[i].x <= contX + contW) && (contY <= mass[i].y) && (mass[i].y <= contY + contL) && (contZ <= mass[i].z) && (mass[i].z <= contZ + contH)) { uPoint++; }
//				}
//			}
//			++iter_coord;
//		}
//	}
//	if (coord.orientation == SIDE) {
//		Coordinatios mass[8] = { Coordinatios(x,y,z,FRONT),  Coordinatios(x + w,y,z,FRONT),  Coordinatios(x,y + l,z,FRONT) , Coordinatios(x,y,z + h,FRONT) ,
//	Coordinatios(x + w,y + l,z,FRONT) , Coordinatios(x + w,y,z + h,FRONT) , Coordinatios(x,y + l,z + h,FRONT) , Coordinatios(x + w,y + l,z + h,FRONT) };
//		while (iter_coord != coorditations.end()) {
//			unsigned int contX = iter_coord->second->x;
//			unsigned int contY = iter_coord->second->y;
//			unsigned int contZ = iter_coord->second->z;
//			unsigned int contL = iter_cont->second->retSize('l');
//			unsigned int contW = iter_cont->second->retSize('w');
//			unsigned int contH = iter_cont->second->retSize('h');
//			for (int i = 0; i < 8; ++i) {
//				if (iter_coord->second->orientation == FRONT) {
//					if ((contX <= mass[i].x) && (mass[i].x <= contX + contL) && (contY <= mass[i].y) && (mass[i].y <= contY + contW) && (contZ <= mass[i].z) && (mass[i].z <= contZ + contH)) { uPoint++; }
//				}
//				if (iter_coord->second->orientation == SIDE) {
//					if ((contX <= mass[i].x) && (mass[i].x <= contX + contW) && (contY <= mass[i].y) && (mass[i].y <= contY + contL) && (contZ <= mass[i].z) && (mass[i].z <= contZ + contH)) { uPoint++; }
//				}
//			}
//			++iter_coord;
//		}
//
//	}
//	if (uPoint > 4)  return false; 
//	else return true;
//}

void Warehouse::getInformation() {
	map<unsigned int, Container*>::iterator iter_cont = containers.begin();
	map<unsigned int, Coordinatios*>::iterator iter_coord = coorditations.begin();
	int num = 1;
	cout << "Number of container :" << containers.size() << endl;
	while (iter_cont != containers.end()) {
		cout << num << ") ";
		cout << "Number: " << iter_cont->first << ", ";
		cout << "Type: " << iter_cont->second->returnType() << ", ";
		iter_cont->second->printInfo();
		cout << "  Coordinations: ";

		cout << "(" << iter_coord->second->x << "," << iter_coord->second->y << "," << iter_coord->second->z << "," << iter_coord->second->orientation << ")\n";
		++num;
		++iter_cont;
		++iter_coord;
	}
}

void Warehouse::resize(unsigned int l, unsigned int w, unsigned int h) {
	if (l >= length and w >= width and h >= height) {
		length = l;
		width = w;
		height = h;
	}
	else { throw std::exception("You cannot reduce the size of the warehouse\n"); }
}

unsigned int Warehouse::getSize(char plane) {
	if (tolower(plane) == 'l') { return length; }
	if (tolower(plane) == 'w') { return width; }
	if (tolower(plane) == 'h') { return height; }
	throw std::exception("Incorrect plane\n");

}
unsigned int Warehouse::getCount() {
	return containersNumber;
}

void Warehouse::showSchema(unsigned int z) {
	Container cont("show", 1, 1, 1, 1, 1, 1);
	Coordinatios p(0, 0, z, FRONT);
	for (int x = 0; x < 5; ++x) {
		for (int y = 0; y < 5; ++y) {
			p.x = x;
			p.y = y;
			if (checkPlace(cont, p) == true) { cout << "o "; }
			else { cout << "x "; }
		}
		cout << endl;
	}
}


bool Warehouse::checkPlace(Container& cont, Coordinatios& coord) {

	bool*** space = new bool** [height];
	for (int i = 0; i < height; i++) {
		space[i] = new bool* [width];
		for (int j = 0; j < width; j++) {
			space[i][j] = new bool[length];
		}
	}

	for (int z = 0; z < height; z++)
		for (int y = 0; y < width; y++)
			for (int x = 0; x < length; x++)
				space[z][y][x] = 0;

	map<unsigned int, Coordinatios*>::iterator iter_coord = coorditations.begin();
	map<unsigned int, Container*>::iterator iter_cont = containers.begin();

	while (iter_coord != coorditations.end()) {
		unsigned int contX = iter_coord->second->x;
		unsigned int contY = iter_coord->second->y;
		unsigned int contZ = iter_coord->second->z;
		unsigned int contL = iter_cont->second->retSize('l');
		unsigned int contW = iter_cont->second->retSize('w');
		unsigned int contH = iter_cont->second->retSize('h');
		if (iter_coord->second->orientation == FRONT) {
			for (int z = contZ; z < contZ+contH; ++z) {
				for (int y = contY; y < contY+contW; ++y) {
					for (int x = contX; x < contX+contL; ++x) {
						space[z][y][x]++;
					}
				}
			}
		}
		if (iter_coord->second->orientation == SIDE) {
			for (int z = contZ; z < contZ + contH; ++z) {
				for (int y = contY; y < contY + contL; ++y) {
					for (int x = contX; x < contX + contW; ++x) {
						space[z][y][x]++;
					}
				}
			}
		}
		++iter_coord;
		++iter_cont;
	}
	unsigned int thisX = coord.x;
	unsigned int thisY = coord.y;
	unsigned int thisZ = coord.z;
	unsigned int thisL = cont.retSize('l');
	unsigned int thisW = cont.retSize('w');
	unsigned int thisH = cont.retSize('h');
	if (coord.orientation == FRONT) {
		for (int z = thisZ; z < thisZ + thisH; ++z) {
			for (int y = thisY; y < thisY + thisW; ++y) {
				for (int x = thisX; x < thisX + thisL; ++x) {
					if(space[z][y][x] == 1) return false;
				}
			}
		}
	}
	if (coord.orientation == SIDE) {
		for (int z = thisZ; z < thisZ + thisW; ++z) {
			for (int y = thisY; y < thisY + thisH; ++y) {
				for (int x = thisX; x < thisX + thisL; ++x) {
					if(space[z][y][x] == 1) return false;
				}
			}
		}
	}
	return true;
}

void Warehouse::rotateContainer(unsigned int num,  char rot) {
	if (rot != FRONT and rot != SIDE) throw std::exception("Incorrect rotation\n");
	if (coorditations[num]->orientation == rot) throw std::exception("This container is already rotated\n");
	if (containers.count(num) == 0) throw std::exception("Incorrect number\n");
	if (rot == FRONT) {
		Coordinatios newCoord(coorditations[num]->x, coorditations[num]->y, coorditations[num]->z, FRONT);
		if (checkPlace(*containers[num], newCoord) == 1) {
			coorditations[num]->orientation == FRONT;
		}
		else throw std::exception("The container can't be rotated\n");
	}
	if (rot == SIDE) {
		Coordinatios newCoord(coorditations[num]->x, coorditations[num]->y, coorditations[num]->z, SIDE);
		if (checkPlace(*containers[num], newCoord) == 1) {
			coorditations[num]->orientation == SIDE;
		}
		else throw std::exception("The container can't be rotated\n");
	}
}

bool Warehouse::checkDown(Container& cont, Coordinatios& coord) {    // 1 - если можем поставить контейнер, 0 - если нет

	bool*** space = new bool** [height];
	for (int i = 0; i < height; i++) {
		space[i] = new bool* [width];
		for (int j = 0; j < width; j++) {
			space[i][j] = new bool[length];
		}
	}

	for (int z = 0; z < height; z++)
		for (int y = 0; y < width; y++)
			for (int x = 0; x < length; x++)
				space[z][y][x] = 0;

	map<unsigned int, Coordinatios*>::iterator iter_coord = coorditations.begin();
	map<unsigned int, Container*>::iterator iter_cont = containers.begin();

	while (iter_coord != coorditations.end()) {
		unsigned int contX = iter_coord->second->x;
		unsigned int contY = iter_coord->second->y;
		unsigned int contZ = iter_coord->second->z;
		unsigned int contL = iter_cont->second->retSize('l');
		unsigned int contW = iter_cont->second->retSize('w');
		unsigned int contH = iter_cont->second->retSize('h');
		if (iter_coord->second->orientation == FRONT) {
			for (int z = contZ; z < contZ + contH; ++z) {
				for (int y = contY; y < contY + contW; ++y) {
					for (int x = contX; x < contX + contL; ++x) {
						space[z][y][x]++;
					}
				}
			}
		}
		if (iter_coord->second->orientation == SIDE) {
			for (int z = contZ; z < contZ + contH; ++z) {
				for (int y = contY; y < contY + contL; ++y) {
					for (int x = contX; x < contX + contW; ++x) {
						space[z][y][x]++;
					}
				}
			}
		}
		++iter_coord;
		++iter_cont;
	}
	unsigned int thisX = coord.x;
	unsigned int thisY = coord.y;
	unsigned int thisZ = coord.z;
	if (thisZ == 0) return true;;
	unsigned int thisL = cont.retSize('l');
	unsigned int thisW = cont.retSize('w');
	unsigned int thisH = cont.retSize('h');
	if (coord.orientation == FRONT) {
		for (int y = thisY; y < thisY + thisW; ++y) {
			for (int x = thisX; x < thisX + thisL; ++x) {
				if (space[thisZ-1][y][x] == 0) return false;
			}
		}
	}
	if (coord.orientation == SIDE) {
		for (int y = thisY; y < thisY + thisH; ++y) {
			for (int x = thisX; x < thisX + thisL; ++x) {
				if (space[thisZ-1][y][x] == 0) return false;
			}
		}
	}
	return true;
}

float Warehouse::chechDownWeight(Coordinatios& coord) {
	if (coord.z == 0) return numeric_limits<float>::max();
	float*** space = new float** [height];
	for (int i = 0; i < height; i++) {
		space[i] = new float* [width];
		for (int j = 0; j < width; j++) {
			space[i][j] = new float[length];
		}
	}

	for (int z = 0; z < height; z++)
		for (int y = 0; y < width; y++)
			for (int x = 0; x < length; x++)
				space[z][y][x] = 0;

	map<unsigned int, Coordinatios*>::iterator iter_coord = coorditations.begin();
	map<unsigned int, Container*>::iterator iter_cont = containers.begin();

	while (iter_coord != coorditations.end()) {
		if (ContainerFragile* p = dynamic_cast<ContainerFragile*>(iter_cont->second)) {
		unsigned int contX = iter_coord->second->x;
		unsigned int contY = iter_coord->second->y;
		unsigned int contZ = iter_coord->second->z;
		unsigned int contL = iter_cont->second->retSize('l');
		unsigned int contW = iter_cont->second->retSize('w');
		unsigned int contH = iter_cont->second->retSize('h');
		if (iter_coord->second->orientation == FRONT) {

			for (int z = contZ; z < contZ + contH; ++z) {
				for (int y = contY; y < contY + contW; ++y) {
					for (int x = contX; x < contX + contL; ++x) {
						space[z][y][x] = p->getMaxmass();
					}
				}
			}
		}
		if (iter_coord->second->orientation == SIDE) {
			for (int z = contZ; z < contZ + contH; ++z) {
				for (int y = contY; y < contY + contL; ++y) {
					for (int x = contX; x < contX + contW; ++x) {
						space[z][y][x] = p->getMaxmass();
					}
				}
			}
		}
	}
		++iter_coord;
		++iter_cont;
	}
	unsigned int thisX = coord.x;
	unsigned int thisY = coord.y;
	unsigned int thisZ = coord.z;
	if (space[thisZ - 1][thisY][thisX] == 0) return numeric_limits<float>::max();
	else return space[thisZ - 1][thisY][thisX];
}

int Warehouse::CalcNumbContainers(Container& cont) {
	int count = 0;
	bool ChTemp = true;
	bool ChMass = true;
	for (int x = 0; x < length-1; ++x) {
		for (int y = 0; y < width-1; ++y) {
			for (int z = 0; z < height-1; ++z) {
				Coordinatios FrontCoord(x, y, z, FRONT);
				Coordinatios SideCoord(x, y, z, SIDE);
				
				if (checkPlace(cont, FrontCoord) == true) {
					if (checkDown(cont, FrontCoord) == true) {
						float maxMassDown = chechDownWeight(FrontCoord);
						if (ContainerCold* p = dynamic_cast<ContainerCold*>(&cont)) {
							if (p->getTemp() < temperature) ChTemp = false;
						}
						if (ContainerFC* p = dynamic_cast<ContainerFC*>(&cont)) {
							if (p->getTemp() < temperature) ChTemp = false;
						}
						if (maxMassDown < cont.getMass()) ChMass = false;
					}
				}
				if (ChMass == true and ChTemp == true) count++;
				else {
					ChMass = true;
					ChTemp = true;
				}

				if (checkPlace(cont, SideCoord) == true) {
					if (checkDown(cont, SideCoord) == true) {
						float maxMassDown = chechDownWeight(SideCoord);
						if (ContainerCold* p = dynamic_cast<ContainerCold*>(&cont)) {
							if (p->getTemp() < temperature) ChTemp = false;
						}
						if (ContainerFC* p = dynamic_cast<ContainerFC*>(&cont)) {
							if (p->getTemp() < temperature) ChTemp = false;
						}
						if (maxMassDown < cont.getMass()) ChMass = false;
					}
				}
				if (ChMass == true and ChTemp == true) count++;
				else {
					ChMass = true;
					ChTemp = true;
				}
			}
		}
	}
	return count;
}

int Warehouse::CalcNumbContainers(Container& cont, char plane) {
	if (plane != FRONT and plane != SIDE) throw std::exception("Wrong orientation\n");
	int count = 0;
	bool ChTemp = true;
	bool ChMass = true;
	for (int x = 0; x < length - 1; ++x) {
		for (int y = 0; y < width - 1; ++y) {
			for (int z = 0; z < height - 1; ++z) {
				if (plane = FRONT) {
					Coordinatios FrontCoord(x, y, z, FRONT);
					if (checkPlace(cont, FrontCoord) == true) {
						if (checkDown(cont, FrontCoord) == true) {
							float maxMassDown = chechDownWeight(FrontCoord);
							if (ContainerCold* p = dynamic_cast<ContainerCold*>(&cont)) {
								if (p->getTemp() < temperature) ChTemp = false;
							}
							if (ContainerFC* p = dynamic_cast<ContainerFC*>(&cont)) {
								if (p->getTemp() < temperature) ChTemp = false;
							}
							if (maxMassDown < cont.getMass()) ChMass = false;
						}
					}
					if (ChMass == true and ChTemp == true) count++;
					else {
						ChMass = true;
						ChTemp = true;
					}
				}
				if (plane = SIDE) {
					Coordinatios SideCoord(x, y, z, SIDE);
					if (checkPlace(cont, SideCoord) == true) {
						if (checkDown(cont, SideCoord) == true) {
							float maxMassDown = chechDownWeight(SideCoord);
							if (ContainerCold* p = dynamic_cast<ContainerCold*>(&cont)) {
								if (p->getTemp() < temperature) ChTemp = false;
							}
							if (ContainerFC* p = dynamic_cast<ContainerFC*>(&cont)) {
								if (p->getTemp() < temperature) ChTemp = false;
							}
							if (maxMassDown < cont.getMass()) ChMass = false;
						}
					}
					if (ChMass == true and ChTemp == true) count++;
					else {
						ChMass = true;
						ChTemp = true;
					}
				}
			}
		}
	}
	return count;
}

void Warehouse::moveContainer(unsigned int num, Coordinatios& coord) {
	if (containers.count(num) == 0) throw std::exception("Incorrect number\n");
	if (checkPlace(*containers[num], coord) == true) {
		if (checkDown(*containers[num], coord) == true) {
			float maxMassDown = chechDownWeight(coord);
			if (ContainerCold* p = dynamic_cast<ContainerCold*>(containers[num])) {
				if (p->getTemp() < temperature) throw std::exception("Warehouse temperature is too high\n");
			}
			if (ContainerFC* p = dynamic_cast<ContainerFC*>(containers[num])) {
				if (p->getTemp() < temperature) throw std::exception("Warehouse temperature is too high\n");
			}
			if (maxMassDown < containers[num]->getMass()) throw std::exception("The container is too heavy\n");
		}
		else throw std::exception("Can't put the container this way\n");
	}
	else throw std::exception("The container can't be placed on this coordinate \n");

	coorditations[num]->x = coord.x;
	coorditations[num]->y = coord.y;
	coorditations[num]->z = coord.z;
	coorditations[num]->orientation = coord.orientation;
}

void Warehouse::deleteContainer(unsigned int num) {
	containers.erase(num);
	coorditations.erase(num);
	map<unsigned int, Coordinatios*>::iterator iter_coord = coorditations.begin();
	map<unsigned int, Container*>::iterator iter_cont = containers.begin();
	while (iter_coord != coorditations.end()) {
		while (checkDown(*iter_cont->second, *iter_coord->second) != 1) {
			iter_coord->second->z--;
		}
		++iter_coord;
		++iter_cont;
	}
	
}

void Warehouse:: autoAddContainer(Container& cont) {
	bool ChTemp = true;
	bool ChMass = true;
	for (int x = 0; x < length - 1; ++x) {
		for (int y = 0; y < width - 1; ++y) {
			for (int z = 0; z < height - 1; ++z) {
				Coordinatios FrontCoord(x, y, z, FRONT);
				Coordinatios SideCoord(x, y, z, SIDE);

				if (checkPlace(cont, FrontCoord) == true) {
					if (checkDown(cont, FrontCoord) == true) {
						float maxMassDown = chechDownWeight(FrontCoord);
						if (ContainerCold* p = dynamic_cast<ContainerCold*>(&cont)) {
							if (p->getTemp() < temperature) ChTemp = false;
						}
						if (ContainerFC* p = dynamic_cast<ContainerFC*>(&cont)) {
							if (p->getTemp() < temperature) ChTemp = false;
						}
						if (maxMassDown < cont.getMass()) ChMass = false;
					}
				}
				if (ChMass == true and ChTemp == true) { addContainer(cont, FrontCoord); break; }
				else {
					ChMass = true;
					ChTemp = true;
				}

				if (checkPlace(cont, SideCoord) == true) {
					if (checkDown(cont, SideCoord) == true) {
						float maxMassDown = chechDownWeight(SideCoord);
						if (ContainerCold* p = dynamic_cast<ContainerCold*>(&cont)) {
							if (p->getTemp() < temperature) ChTemp = false;
						}
						if (ContainerFC* p = dynamic_cast<ContainerFC*>(&cont)) {
							if (p->getTemp() < temperature) ChTemp = false;
						}
						if (maxMassDown < cont.getMass()) ChMass = false;
					}
				}
				if (ChMass == true and ChTemp == true) { addContainer(cont, FrontCoord); break; }
				else {
					ChMass = true;
					ChTemp = true;
				}
			}
		}
	}
	throw std::exception("It is not possible to add a container\n");
}