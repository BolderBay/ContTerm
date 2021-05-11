#include "ContainerFC.h" 
#include "ContainerTerminalConsts.h"
using namespace ContainerTerminalConsts;

struct Coordinatios  // дальний левый нижний угол
{
	int x;
	int y;
	int z;
	char orientation;
};

class Warehouse
{
private:
	int containersNumber;
	int length;
	int width;
	int height;
	float temperature;
	Container* containers;		// лучше взять коллекцию контейнеров из STL нпример вектор или map
	Coordinatios* coord;
public:
	void rotate();
	void getType();

	void addContainer();
	void moveContainer();
	void rotateContainer();
	void deleteContainer();
	void getInformation();
	void autoAddContainer();
	void CalcNumbContainers();
};

