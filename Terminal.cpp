#include "Terminal.h"

Terminal::Terminal() {
	Warehouse ware;
	listOfWarehouse.insert(pair<unsigned int, Warehouse*>(0, &ware));
}

Terminal::Terminal(unsigned int num, Warehouse& ware) {
	listOfWarehouse.insert(pair<unsigned int, Warehouse*>(num, &ware));
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
	cout << "Number of warehouses: " << listOfWarehouse.size() << endl;
	int num = 1;
	while (iter_ware != listOfWarehouse.end()) {
		cout << num << ") ";
		cout << "Number: " << iter_ware->first << ", ";
		cout << "Size: (" << iter_ware->second->getSize('l') << ',' << iter_ware->second->getSize('w') << ',' << iter_ware->second->getSize('h') << "), ";
		cout << "Number of containers: " << iter_ware->second->getCount() << endl;
		++iter_ware;
	}
}

void Terminal::delWarehouse(unsigned int num) {
	listOfWarehouse.erase(num);
}