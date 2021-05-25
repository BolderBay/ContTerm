#include "ContainerFC.h" 
#include "ContainerTerminalConsts.h"

#include <iostream>
#include <map>   
using namespace std;
using namespace ContainerTerminalConsts;

struct Coordinatios  // Дальний левый нижний угол
{
	unsigned int x;
	unsigned int y;
	unsigned int z;
	char orientation;
	Coordinatios() { x = 1; y = 1; z = 1; orientation = FRONT;}
	Coordinatios(unsigned int wx, unsigned int wy, unsigned int wz, char wo) { 
		if (wo != FRONT and wo != SIDE) throw std::exception("Incorrect plane\n");
		else {
			x = wx; 
			y = wy; 
			z = wz; 
			orientation = wo;
		}
	}
};

class Warehouse
{
private:
	unsigned int containersNumber;							// Число контейнеров
	unsigned int length;
	unsigned int width;
	unsigned int height;
	float temperature;
	map <unsigned int, Container*> containers;
	map <unsigned int, Coordinatios*> coorditations;

	bool checkPlace(Container& cont, Coordinatios& coord);	// Проверка пересечения контейнеров
	bool checkDown(Container& cont, Coordinatios& coord);	// Проверка наличия контейнеров под устанавливаемым
	float chechDownWeight(Coordinatios& coord);				// Максимальная масса нижнего контейнера

public:
	Warehouse();
	Warehouse(unsigned int l, unsigned int w, unsigned int h, float t);
	~Warehouse();

	std::string getType(unsigned int num);
	float getTemp(unsigned int num);
	float getMaxmass(unsigned int num);
	void addContainer(Container& cont, Coordinatios& coord);
	void getInformation();
	void resize(unsigned int l, unsigned int w, unsigned int h);
	unsigned int getSize(char plane);
	unsigned int getCount();
	void rotateContainer(unsigned int num, char rot);
	int CalcNumbContainers(Container &cont);
	int CalcNumbContainers(Container& cont, char plane);
	void moveContainer(unsigned int num, Coordinatios& coord);
	void deleteContainer(unsigned int num);
	void autoAddContainer(Container& cont);
	void showSchema(unsigned int z);
};

