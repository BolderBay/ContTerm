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
	unsigned int number;
	map <unsigned int, Warehouse*> listOfWarehouse;
public:
	Terminal();
	Terminal(unsigned int num);
	Terminal(unsigned int num, unsigned int warenum, Warehouse& ware);
	~Terminal();

	Terminal(Terminal& term);
	Terminal(Terminal&& term);

	void addWarehouse(unsigned int num, Warehouse& ware);
	void resizeWarehouse(unsigned int num, unsigned int l, unsigned int w, unsigned int h);
	void getInformation();
	void delWarehouse(unsigned int num);

	unsigned int getNum();
	void setNum(unsigned int num);
	void getInformWare(unsigned int num);
	void getInformCont(unsigned int num, unsigned int numcont);
	void addContainer(unsigned int num, Container& cont, Coordinatios& coord);
	void autoAddContainer(unsigned int num, Container& cont);
	void rotCont(unsigned int num, unsigned int number, char side);
	void moveCont(unsigned int num, unsigned int number, Coordinatios& coord);
	void delCont(unsigned int num, unsigned int number);
	void showSchema(unsigned int num, unsigned int floor);

	void save();
	void load(unsigned int num);
};


