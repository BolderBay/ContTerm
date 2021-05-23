#include "Container.h"

class ContainerFragile : virtual public Container {
protected:
	float maxmass;
public:
	ContainerFragile();
	ContainerFragile(std::string comp, unsigned int num, unsigned int l, unsigned int w, unsigned int h, float cst, float ms, float mxm);
	void printInfo();
	std::string returnType();
};