#include "ContainerCold.h"
#include "ContainerFragile.h"

class ContainerFC : public ContainerCold, public ContainerFragile { 
private:
public:
	ContainerFC();
	ContainerFC(std::string comp, unsigned int num, unsigned int l, unsigned int w, unsigned int h, float cst, float ms, float mxt, float mxm);
	void printInfo();
	std::string forSave();
	std::string returnType();
};