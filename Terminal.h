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
	map <Warehouse, int> listOfWarehouse;
public:
	void addWarehouse();
	void delWarehouse();
	void resizeWarehouse();
	void getInformation();
};

