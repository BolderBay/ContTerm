#include "ContainerFC.h" 
#include "ContainerTerminalConsts.h"

#include <iostream>
#include <map>   
using namespace std;
using namespace ContainerTerminalConsts;

struct Coordinatios  // дальний левый нижний угол
{
	unsigned int x;
	unsigned int y;
	unsigned int z;
	char orientation;
	Coordinatios() { x = 1; y = 1; z = 1; orientation = FRONT;}
	Coordinatios(unsigned int wx, unsigned int wy, unsigned int wz, char wo) { x = wx;  y = wy; z = wz; orientation = wo;}
};

class Warehouse
{
private:
	unsigned int containersNumber;			//Число контейнеров
	unsigned int length;
	unsigned int width;
	unsigned int height;
	float temperature;
	map <unsigned int, Container*> containers;
	map <unsigned int, Coordinatios*> coorditations;

public:
	bool checkPlace(Container& cont, Coordinatios& coord);

	Warehouse();
	Warehouse(unsigned int l, unsigned int w, unsigned int h, float t);
	//~Warehouse();

	std::string getType(unsigned int num);
	float getTemp(unsigned int num);
	float getMaxmass(unsigned int num);

	void addContainer(Container& cont, Coordinatios& coord);
	void getInformation();
	void resize(unsigned int l, unsigned int w, unsigned int h);
	unsigned int getSize(char plane);
	unsigned int getCount();

	void moveContainer();
	void rotateContainer();
	void deleteContainer();
	void autoAddContainer();
	void CalcNumbContainers();

	void showSheme();
};

