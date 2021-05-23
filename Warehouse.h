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
};

class Warehouse
{
private:
	unsigned int containersNumber;			//Число контейнеров
	unsigned int length;
	unsigned int width;
	unsigned int height;
	float temperature;
	map <int, Container*> containers;
	map <int, Coordinatios> coorditations;
public:
	Warehouse();
	Warehouse(unsigned int l, unsigned int w, unsigned int h, float t);

	void rotate();
	std::string getType(unsigned int num);

	float getTemp(unsigned int num);

	void addContainer(Container& cont, Coordinatios coord);
	void moveContainer();
	void rotateContainer();
	void deleteContainer();
	void getInformation();
	void autoAddContainer();
	void CalcNumbContainers();
};

