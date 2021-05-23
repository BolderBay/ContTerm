#include "Container.h"

class ContainerCold : virtual public Container {
protected:
	float maxtemp;
public:
	ContainerCold();
	ContainerCold(std::string comp, unsigned int num, unsigned int l, unsigned int w, unsigned int h, float cst, float ms, float mxt);
	void printInfo();
	std::string returnType();

	float getTemp();
};

