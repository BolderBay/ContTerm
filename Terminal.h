#include "Warehouse.h" 
#include "ContainerTerminalConsts.h"
#include <iostream>
#include <map>   
using namespace std;
using namespace ContainerTerminalConsts;
using namespace ContainerTerminalConsts;


class Terminal
{
private:
	map <unsigned int, Warehouse*> listOfWarehouse;
public:
	Terminal();
	Terminal(unsigned int num, Warehouse& ware);
	~Terminal();

	void addWarehouse(unsigned int num, Warehouse& ware);
	void resizeWarehouse(unsigned int num, unsigned int l, unsigned int w, unsigned int h);
	void getInformation();
	void delWarehouse(unsigned int num);

};

