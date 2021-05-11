#include "Warehouse.h" 
#include "ContainerTerminalConsts.h"
using namespace ContainerTerminalConsts;


class Terminal
{
private:
	Warehouse* listOfWarehouse;		//тоже stl, лучше map
	int* numerOfWarehouse;
public:
	void addWarehouse();
	void delWarehouse();
	void resizeWarehouse();
	void getInformation();
};

