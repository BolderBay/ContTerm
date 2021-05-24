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

//Warehouse::~Warehouse() {
//	map<unsigned int, Container*>::iterator iter_cont = containers.begin();
//	map<unsigned int, Coordinatios*>::iterator iter_coord = coorditations.begin();
//	while (iter_cont != containers.end()) {
//		delete iter_cont->second;
//		delete iter_coord->second;
//		iter_cont->second = nullptr;
//		iter_coord->second = nullptr;
//		++iter_cont;
//		++iter_coord;
//	}
//}

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

bool Warehouse::checkPlace(Container& cont, Coordinatios& coord)  {
	unsigned int x = coord.x;
	unsigned int y = coord.y;
	unsigned int z = coord.z;
	unsigned int l = cont.retSize('l');
	unsigned int w = cont.retSize('w');
	unsigned int h = cont.retSize('h');
	map<unsigned int, Coordinatios*>::iterator iter_coord = coorditations.begin();
	if (coord.orientation == FRONT) {
		Coordinatios mass[8] = { Coordinatios(x,y,z,FRONT),  Coordinatios(x+l,y,z,FRONT),  Coordinatios(x,y+w,z,FRONT) , Coordinatios(x,y,z+h,FRONT) , 
			Coordinatios(x+l,y+w,z,FRONT) , Coordinatios(x+l,y,z+h,FRONT) , Coordinatios(x,y+w,z+h,FRONT) , Coordinatios(x+l,y+w,z+h,FRONT) };
		while (iter_coord != coorditations.end()){
			unsigned int contX = iter_coord->second->x;
			unsigned int contY = iter_coord->second->y;
			unsigned int contZ = iter_coord->second->z;
			for (int i = 0; i < 8; ++i) {
				if (iter_coord->second->orientation == FRONT) {
					if ((contX < mass[i].x) && (mass[i].x < contX + l) && (contY < mass[i].y) && (mass[i].y < contY + w) && (contZ < mass[i].z) && (mass[i].z < contZ + h)) { return false; }
				}
				if (iter_coord->second->orientation == SIDE) {
					if ((contX < mass[i].x) && (mass[i].x < contX + w) && (contY < mass[i].y) && (mass[i].y < contY + l) && (contZ < mass[i].z) && (mass[i].z < contZ + h)) { return false; }
				}
			}
			++iter_coord;
		}
	}
	if (coord.orientation == SIDE) {
		Coordinatios mass[8] = { Coordinatios(x,y,z,FRONT),  Coordinatios(x + w,y,z,FRONT),  Coordinatios(x,y + l,z,FRONT) , Coordinatios(x,y,z + h,FRONT) ,
	Coordinatios(x + w,y + l,z,FRONT) , Coordinatios(x + w,y,z + h,FRONT) , Coordinatios(x,y + l,z + h,FRONT) , Coordinatios(x + w,y + l,z + h,FRONT) };
		while (iter_coord != coorditations.end()) {
			unsigned int contX = iter_coord->second->x;
			unsigned int contY = iter_coord->second->y;
			unsigned int contZ = iter_coord->second->z;
			for (int i = 0; i < 8; ++i) {
				if (iter_coord->second->orientation == FRONT) {
					if ((contX < mass[i].x) && (mass[i].x < contX + l) && (contY < mass[i].y) && (mass[i].y < contY + w) && (contZ < mass[i].z) && (mass[i].z < contZ + h)) { return false; }
				}
				if (iter_coord->second->orientation == SIDE) {
					if ((contX < mass[i].x) && (mass[i].x < contX + w) && (contY < mass[i].y) && (mass[i].y < contY + l) && (contZ < mass[i].z) && (mass[i].z < contZ + h)) { return false; }
				}
			}
			++iter_coord;
		}

	}
	return true;
}

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
	else { std::exception("You cannot reduce the size of the warehouse\n"); }
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

void Warehouse::showSheme() {
	Container cont("US", 322, 1, 1, 0, 500, 100);
	Coordinatios p(0, 0, 0, FRONT);
	for (int x = 0; x < 5; ++x) {
		for (int y = 0; y < 5; ++y) {
			p.x = x;
			p.y = y;
			if (this->checkPlace(cont, p) == true) { cout << '1'; }
			else { cout << '0'; }
		}
		cout << endl;
	}
}
