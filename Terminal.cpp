#include "Terminal.h"
#include <iostream>
#include <fstream>

Terminal::Terminal() {
	number = 0;
}

Terminal::Terminal(unsigned int num) {
	number = num;
}

Terminal::Terminal(unsigned int num, unsigned int warenum, Warehouse& ware) {
	number = num;
	listOfWarehouse.insert(pair<unsigned int, Warehouse*>(warenum, &ware));
}

Terminal::Terminal(Terminal& term) {
	number = term.number;
	map <unsigned int, Warehouse*>::iterator iter_ware = term.listOfWarehouse.begin();
	while (iter_ware != listOfWarehouse.end()) {
		listOfWarehouse[term.number] = iter_ware->second;
		++iter_ware;
	}

}
Terminal::Terminal(Terminal&& term) {
	number = term.number;
	listOfWarehouse = term.listOfWarehouse;
}

Terminal::~Terminal() {
	map <unsigned int, Warehouse*>::iterator iter_ware = listOfWarehouse.begin();
	while (iter_ware != listOfWarehouse.end()) {
		delete iter_ware->second;
		iter_ware->second = nullptr;
		++iter_ware;	
	}
}
void Terminal::addWarehouse(unsigned int num, Warehouse& ware) {
	listOfWarehouse.insert(pair<unsigned int, Warehouse*>(num, &ware));
}

void Terminal::resizeWarehouse(unsigned int num, unsigned int l, unsigned int w, unsigned int h) {
	listOfWarehouse[num]->resize(l, w, h);
}

void Terminal::getInformation() {
	map <unsigned int, Warehouse*>::iterator iter_ware;
	iter_ware = listOfWarehouse.begin();
	cout << "   Number of warehouses: " << listOfWarehouse.size() << endl;
	int num = 1;
	while (iter_ware != listOfWarehouse.end()) {
		cout << num << ") ";
		cout << "Number: " << iter_ware->first << ", ";
		cout << "Size: (" << iter_ware->second->getSize('l') << ',' << iter_ware->second->getSize('w') << ',' << iter_ware->second->getSize('h') << "), ";
		cout << "Number of containers: " << iter_ware->second->getCount() << endl;
		++iter_ware;
		++num;
	}
}

void Terminal::delWarehouse(unsigned int num) {
	listOfWarehouse.erase(num);
}


unsigned int Terminal::getNum() {
	return number;
}

void Terminal::setNum(unsigned int num) {
	number = num;
}
void Terminal::getInformWare(unsigned int num) {
	if (listOfWarehouse.count(num) == 0) { throw std::exception("Incorrect number\n"); }
	listOfWarehouse[num]->getInformation();
}
void Terminal::getInformCont(unsigned int num, unsigned int numcont) {
	if (listOfWarehouse.count(num) == 0) { throw std::exception("Incorrect number\n"); }
	listOfWarehouse[num]->printinfocontainer(numcont);
}

void Terminal::addContainer(unsigned int num, Container& cont, Coordinatios& coord) {
	if (listOfWarehouse.count(num) == 0) { throw std::exception("Incorrect number\n"); }
	listOfWarehouse[num]->addContainer(cont, coord);
}
void Terminal::autoAddContainer(unsigned int num, Container& cont) {
	if (listOfWarehouse.count(num) == 0) { throw std::exception("Incorrect number\n"); }
	listOfWarehouse[num]->autoAddContainer(cont);
}
void Terminal::rotCont(unsigned int num, unsigned int number, char side) {
	if (listOfWarehouse.count(num) == 0) { throw std::exception("Incorrect number\n"); }
	listOfWarehouse[num]->rotateContainer(number, side);
}
void Terminal::moveCont(unsigned int num, unsigned int number, Coordinatios& coord) {
	if (listOfWarehouse.count(num) == 0) { throw std::exception("Incorrect number\n"); }
	listOfWarehouse[num]->moveContainer(number, coord);
}
void Terminal::delCont(unsigned int num, unsigned int number) {
	if (listOfWarehouse.count(num) == 0) { throw std::exception("Incorrect number\n"); }
	listOfWarehouse[num]->deleteContainer(number);

}

void Terminal::showSchema(unsigned int num, unsigned int floor) {
	if (listOfWarehouse.count(num) == 0) { throw std::exception("Incorrect number\n"); }
	listOfWarehouse[num]->showSchema(floor);
}

void Terminal::save() {
	if (listOfWarehouse.size() == 0) { throw std::exception("Zero terminal\n"); }

	map <unsigned int, Warehouse*>::iterator iter_ware = listOfWarehouse.begin();

	std::ofstream out;									// поток для записи
	out.open("F:\\file"+ to_string(number)+".dat");     // окрываем файл для записи
	if (out.is_open())
	{
		out << number << endl;								  //номер терминала
		out << listOfWarehouse.size() << endl;			      //количество складов
		while (iter_ware != listOfWarehouse.end()) {	
			out << iter_ware->first << endl;		          //номер склада
			out << iter_ware->second->getSize('l') << " " << iter_ware->second->getSize('w') << " " << iter_ware->second->getSize('h') << " " << iter_ware->second->getTempWare() << endl; //размеры склада и температура
			out << iter_ware->second->getCount() << endl;     //количество контейнеров
			iter_ware->second->forSave(out);				  //информация о контейнерах
			++iter_ware;
		}

	}

	out.close();
}

void Terminal::load(unsigned int num)
{
	unsigned int le;
	unsigned int wi;
	unsigned int he;
	float te;
	std::string company;
	unsigned int number;
	unsigned int length;
	unsigned int width;
	unsigned int height;
	float cost;
	float mass;
	float maxmass;
	float maxtemp;
	unsigned int x;
	unsigned int y;
	unsigned int z;
	char orientation;
	unsigned int count;
	unsigned int warenum;
	unsigned int contnum;
	std::string line;

	std::ifstream in("F:\\file" + to_string(num) + ".dat"); { // окрываем файл для чтения
		if (in.is_open())
		{
			getline(in, line);
			number = stoi(line);				//номер терминала
			getline(in, line);
			count = stoi(line);					//ко-во складов
			for (int i = 0; i < count; ++i) {
				getline(in, line);
				warenum = stoi(line);			//номер скалада
				in >> le >> wi >> he >> te;	    //размеры склада
				Warehouse ware(le, wi, he, te);
				getline(in, line);
				getline(in, line);
				contnum = stoi(line);			//кол-во контейнеров
				for (int j = 0; j < contnum; ++j) {
					getline(in, line);
					if (line == "Container") {
						in >> company >> number >> length >> width >> height >> cost >> mass;
						Container container(company, number, length, width, height, cost, mass);
						in >> x >> y >> z >> orientation;
						Coordinatios coord(x, y, z, orientation);
						ware.addContainer(container, coord);
					}
					if (line == "ContainerCold") {
						in >> company >> number >> length >> width >> height >> cost >> mass >> maxtemp;
						ContainerCold container(company, number, length, width, height, cost, mass, maxtemp);
						in >> x >> y >> z >> orientation;
						Coordinatios coord(x, y, z, orientation);
						ware.addContainer(container, coord);
					}
					if (line == "ContainerFragile") {
						in >> company >> number >> length >> width >> height >> cost >> mass >> maxmass;
						ContainerFragile container(company, number, length, width, height, cost, mass, maxmass);
						in >> x >> y >> z >> orientation;
						Coordinatios coord(x, y, z, orientation);
						ware.addContainer(container, coord);
					}
					if (line == "ContainerFC") {
						in >> company >> number >> length >> width >> height >> cost >> mass >> maxtemp >> maxmass;
						ContainerFC container(company, number, length, width, height, cost, mass, maxtemp, maxmass);
						in >> x >> y >> z >> orientation;
						Coordinatios coord(x, y, z, orientation);
						ware.addContainer(container, coord);
					}
					getline(in, line);
				}
				listOfWarehouse[warenum] = &ware;
			}

			in.close();     // закрываем файл
		}
	}
}