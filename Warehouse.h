#include "ContainerFC.h" 
#include "ContainerTerminalConsts.h"
using namespace ContainerTerminalConsts;

struct Coordinatios  // ������� ����� ������ ����
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
	Container* containers;		// ����� ����� ��������� ����������� �� STL ������� ������ ��� map
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

