#include "Warehouse.h"
#include <iostream>
#include <iomanip>
#include <fstream>

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

Warehouse::Warehouse(Warehouse& ware) {
	containersNumber = ware.getCount();
	length = ware.getSize('l');
	width = ware.getSize('w');
	height = ware.getSize('h');
	temperature = ware.getTempWare();
	map <unsigned int, pair<Container*, Coordinatios*>>::iterator iter_contmap = ware.contmap.begin();
	while (iter_contmap != ware.contmap.end()) {
		contmap[iter_contmap->first] = { iter_contmap->second.first, iter_contmap->second.second };
		++iter_contmap;
	}	
}

Warehouse::Warehouse(Warehouse&& ware) {
	containersNumber = ware.containersNumber;
	length = ware.length;
	width = ware.width;
	height = ware.height;
	temperature = ware.temperature;
	contmap = ware.contmap;
}

Warehouse::~Warehouse() {
	map <unsigned int, pair<Container*, Coordinatios*>>::iterator iter_contmap = contmap.begin();
	while (iter_contmap != contmap.end()) {
		delete iter_contmap->second.first;
		delete iter_contmap->second.second;
		iter_contmap->second.first = nullptr;
		iter_contmap->second.second = nullptr;
		++iter_contmap;
	}
}

std::string Warehouse::getType(unsigned int num) {
	if (contmap.count(num) >= 1) {
		if (ContainerCold* p = dynamic_cast<ContainerCold*>(contmap[num].first)) { return p->returnType(); }
		if (ContainerFragile* p = dynamic_cast<ContainerFragile*>(contmap[num].first)) { return p->returnType(); }
		if (ContainerFC* p = dynamic_cast<ContainerFC*>(contmap[num].first)) { return p->returnType(); }
		return contmap[num].first->returnType();
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
	

	
	contmap.insert({ cont.getNumber(), pair<Container*, Coordinatios*>(&cont,&coord) });
	containersNumber = contmap.size();

}

float Warehouse::getTemp(unsigned int num) {
	if (ContainerCold* p = dynamic_cast<ContainerCold*>(contmap[num].first)) { return p->getTemp();}
	else {throw std::exception("This is not a refrigerated container \n"); }
	
}

float Warehouse::getMaxmass(unsigned int num) {
	if (ContainerFragile* p = dynamic_cast<ContainerFragile*>(contmap[num].first)) { return p->getMaxmass(); }
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
	map <unsigned int, pair<Container*, Coordinatios*>>::iterator iter_contmap = contmap.begin();

	int num = 1;
	cout << "Number of container :" << contmap.size() << endl;
	while (iter_contmap != contmap.end()) {
		cout << num << ") ";
		cout << "Number: " << iter_contmap->first << ", ";
		cout << "Type: " << iter_contmap->second.first->returnType() << ", ";
		iter_contmap->second.first->printInfo();
		cout << "  Coordinations: ";

		cout << "(" << iter_contmap->second.second->x << "," << iter_contmap->second.second->y << "," << iter_contmap->second.second->z << "," << iter_contmap->second.second->orientation << ")\n";
		++num;
		++iter_contmap;
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
	return true;
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

	map <unsigned int, pair<Container*, Coordinatios*>>::iterator iter_contmap = contmap.begin();

	while (iter_contmap != contmap.end()) {
		unsigned int contX = iter_contmap->second.second->x;
		unsigned int contY = iter_contmap->second.second->y;
		unsigned int contZ = iter_contmap->second.second->z;
		unsigned int contL = iter_contmap->second.first->retSize('l');
		unsigned int contW = iter_contmap->second.first->retSize('w');
		unsigned int contH = iter_contmap->second.first->retSize('h');
		if (iter_contmap->second.second->orientation == FRONT) {
			for (int z = contZ; z < contZ+contH; ++z) {
				for (int y = contY; y < contY+contW; ++y) {
					for (int x = contX; x < contX+contL; ++x) {
						space[z][y][x]++;
					}
				}
			}
		}
		if (iter_contmap->second.second->orientation == SIDE) {
			for (int z = contZ; z < contZ + contH; ++z) {
				for (int y = contY; y < contY + contL; ++y) {
					for (int x = contX; x < contX + contW; ++x) {
						space[z][y][x]++;
					}
				}
			}
		}
		++iter_contmap;
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
					if (x > length or y > width or z > height) { return false; }
					if(space[z][y][x] == 1) return false;
				}
			}
		}
	}
	if (coord.orientation == SIDE) {
		for (int z = thisZ; z < thisZ + thisW; ++z) {
			for (int y = thisY; y < thisY + thisH; ++y) {
				for (int x = thisX; x < thisX + thisL; ++x) {
					if (x > length or y > width or z > height) { return false; }
					if(space[z][y][x] == 1) return false;
				}
			}
		}
	}
	return true;
}

void Warehouse::rotateContainer(unsigned int num,  char rot) {
	if (rot != FRONT and rot != SIDE) throw std::exception("Incorrect rotation\n");
	if (contmap[num].second->orientation == rot) throw std::exception("This container is already rotated\n");
	if (contmap.count(num) == 0) throw std::exception("Incorrect number\n");
	if (rot == FRONT) {
		Coordinatios newCoord(contmap[num].second->x, contmap[num].second->y, contmap[num].second->z, FRONT);
		if (checkPlace(*contmap[num].first, newCoord) == 1) {
			contmap[num].second->orientation == FRONT;
		}
		else throw std::exception("The container can't be rotated\n");
	}
	if (rot == SIDE) {
		Coordinatios newCoord(contmap[num].second->x, contmap[num].second->y, contmap[num].second->z, SIDE);
		if (checkPlace(*contmap[num].first, newCoord) == 1) {
			contmap[num].second->orientation == SIDE;
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

	map <unsigned int, pair<Container*, Coordinatios*>>::iterator iter_contmap = contmap.begin();

	while (iter_contmap != contmap.end()) {
		unsigned int contX = iter_contmap->second.second->x;
		unsigned int contY = iter_contmap->second.second->y;
		unsigned int contZ = iter_contmap->second.second->z;
		unsigned int contL = iter_contmap->second.first->retSize('l');
		unsigned int contW = iter_contmap->second.first->retSize('w');
		unsigned int contH = iter_contmap->second.first->retSize('h');
		if (iter_contmap->second.second->orientation == FRONT) {
			for (int z = contZ; z < contZ + contH; ++z) {
				for (int y = contY; y < contY + contW; ++y) {
					for (int x = contX; x < contX + contL; ++x) {
						space[z][y][x]++;
					}
				}
			}
		}
		if (iter_contmap->second.second->orientation == SIDE) {
			for (int z = contZ; z < contZ + contH; ++z) {
				for (int y = contY; y < contY + contL; ++y) {
					for (int x = contX; x < contX + contW; ++x) {
						space[z][y][x]++;
					}
				}
			}
		}
		++iter_contmap;
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

	map <unsigned int, pair<Container*, Coordinatios*>>::iterator iter_contmap = contmap.begin();

	while (iter_contmap != contmap.end()) {
		if (ContainerFragile* p = dynamic_cast<ContainerFragile*>(iter_contmap->second.first)) {
		unsigned int contX = iter_contmap->second.second->x;
		unsigned int contY = iter_contmap->second.second->y;
		unsigned int contZ = iter_contmap->second.second->z;
		unsigned int contL = iter_contmap->second.first->retSize('l');
		unsigned int contW = iter_contmap->second.first->retSize('w');
		unsigned int contH = iter_contmap->second.first->retSize('h');
		if (iter_contmap->second.second->orientation == FRONT) {

			for (int z = contZ; z < contZ + contH; ++z) {
				for (int y = contY; y < contY + contW; ++y) {
					for (int x = contX; x < contX + contL; ++x) {
						space[z][y][x] = p->getMaxmass();
					}
				}
			}
		}
		if (iter_contmap->second.second->orientation == SIDE) {
			for (int z = contZ; z < contZ + contH; ++z) {
				for (int y = contY; y < contY + contL; ++y) {
					for (int x = contX; x < contX + contW; ++x) {
						space[z][y][x] = p->getMaxmass();
					}
				}
			}
		}
	}
		++iter_contmap;
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
	if (contmap.count(num) == 0) throw std::exception("Incorrect number\n");
	if (checkPlace(*contmap[num].first, coord) == true) {
		if (checkDown(*contmap[num].first, coord) == true) {
			float maxMassDown = chechDownWeight(coord);
			if (ContainerCold* p = dynamic_cast<ContainerCold*>(contmap[num].first)) {
				if (p->getTemp() < temperature) throw std::exception("Warehouse temperature is too high\n");
			}
			if (ContainerFC* p = dynamic_cast<ContainerFC*>(contmap[num].first)) {
				if (p->getTemp() < temperature) throw std::exception("Warehouse temperature is too high\n");
			}
			if (maxMassDown < contmap[num].first->getMass()) throw std::exception("The container is too heavy\n");
		}
		else throw std::exception("Can't put the container this way\n");
	}
	else throw std::exception("The container can't be placed on this coordinate \n");

	contmap[num].second->x = coord.x;
	contmap[num].second->y = coord.y;
	contmap[num].second->z = coord.z;
	contmap[num].second->orientation = coord.orientation;
}

void Warehouse::deleteContainer(unsigned int num) {
	if (contmap.count(num) == 0) {throw std::exception("Incorrect number;\n");}
	contmap.erase(num);
	map <unsigned int, pair<Container*, Coordinatios*>>::iterator iter_contmap = contmap.begin();
	while (iter_contmap != contmap.end()) {
		while (checkDown(*iter_contmap->second.first, *iter_contmap->second.second) != 1) {
			iter_contmap->second.second->z--;
		}
		++iter_contmap;
	}
	
}

void Warehouse::autoAddContainer(Container& cont) {
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

void Warehouse::write() {
	fstream file;
	file.open("test", ios::app | ios::binary);
	file.write(reinterpret_cast<char*>(this), sizeof(this));
}

void Warehouse::read() {
	fstream file;
	file.open("test", ios::app | ios::binary);
	file.read(reinterpret_cast<char*>(this), sizeof(this));
}

void Warehouse::printinfocontainer(unsigned int num) {
	if (contmap.count(num) > 0) {
		contmap[num].first->printInfo();
	}
	else throw std::exception("Incorrect number\n");
}

float Warehouse::getTempWare() {
	return temperature;
}

void Warehouse::forSave(std::ostream& out) {
	map <unsigned int, pair<Container*, Coordinatios*>>::iterator iter_contmap = contmap.begin();
	while (iter_contmap != contmap.end()) {
		out << iter_contmap->second.first->returnType() << endl;  //тип контейнера
		out << iter_contmap->second.first->forSave() << endl; //данные о контейнере
		out << iter_contmap->second.second->x << " " << iter_contmap->second.second->y << " " << iter_contmap->second.second->z << " " << iter_contmap->second.second->orientation << endl;  //данные о местоположении
		++iter_contmap;
	}
}