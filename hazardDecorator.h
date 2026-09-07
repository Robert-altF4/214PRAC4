#ifndef HAZARDDECORATOR_H
#define HAZARDDECORATOR_H

#include "ProjectDecorator.h"
#include <iostream>
#include "ProjectComponent.h"

class hazardDecorator : public ProjectDecorator {

public:
	std::string warning;

	hazardDecorator(ProjectComponent* x, std::string w);

	virtual int getCost();

	virtual int getTime();
};

#endif
