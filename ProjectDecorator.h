#ifndef PROJECTDECORATOR_H
#define PROJECTDECORATOR_H

#include "ProjectComponent.h"

class ProjectDecorator : public ProjectComponent {

public:
	ProjectComponent* target;

	ProjectDecorator(ProjectComponent* t);

	virtual void add(ProjectComponent* x){}

	virtual void remove(ProjectComponent* x){}

	virtual ~ProjectDecorator();
	virtual ProjectIterator* createIIterator(std::string type);
};

#endif
