#ifndef RUSHDECORATOR_H
#define RUSHDECORATOR_H

#include "ProjectDecorator.h"
#include "ProjectComponent.h"

class rushDecorator : public ProjectDecorator {


public:
	rushDecorator(ProjectComponent* x);

	virtual int getCost();

	virtual int getTime();
};

#endif
