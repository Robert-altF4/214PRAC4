#ifndef PROJECTCOMPONENT_H
#define PROJECTCOMPONENT_H

#include <iostream>
#include <string>

class ProjectIterator;



class ProjectComponent {
public:
	virtual void add(ProjectComponent* x) = 0;
	virtual void remove(ProjectComponent* x) = 0;
	ProjectComponent();

public:
	virtual int getCost() = 0;

	virtual int getTime() = 0;

	virtual ProjectIterator* createIIterator(std::string type) = 0;

	virtual ~ProjectComponent();
};

#endif
