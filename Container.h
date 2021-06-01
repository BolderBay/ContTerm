#pragma once
#include <iostream>
#include <string>
#include "ContainerTerminalConsts.h"

using namespace ContainerTerminalConsts;

class Container
{
protected:
	std::string company;
	unsigned int number;
	unsigned int length;
	unsigned int width;
	unsigned int height;
	float cost;
	float mass;

public:
	Container();
	Container(std::string comp, unsigned int num, unsigned int l, unsigned int w, unsigned int h, float cst, float ms);
	virtual void printInfo();
	virtual std::string forSave();
	virtual std::string returnType();
	float getMass();
	unsigned int getNumber();
	unsigned int retSize(char plane);
	void setNumber(unsigned int num);
	void setSize(unsigned int x, unsigned int y, unsigned int z);
};
