#ifndef PROJECTCOMPONENT_H
#define PROJECTCOMPONENT_H

#include <iostream>
#include <string>

//#include "ProjectIterator.h"



class ProjectComponent {
public:
	virtual void add(ProjectComponent* x) = 0;
	virtual void remove(ProjectComponent* x) = 0;
	ProjectComponent();

public:
	virtual int getCost() = 0;

	virtual int getTime() = 0;

	//ProjectIterator* createIIterator(std::string type);

	virtual ~ProjectComponent();
};

#endif
