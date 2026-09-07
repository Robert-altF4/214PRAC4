#ifndef PROJECTGROUP_H
#define PROJECTGROUP_H

#include "ProjectComponent.h"

#include <vector>


class ProjectGroup : public ProjectComponent {
	friend class DepthFirstIterator;
private:
std::vector<ProjectComponent*> components;

public:
	virtual int getCost();

	virtual int getTime();

	virtual void add(ProjectComponent* x);

	virtual void remove(ProjectComponent* x);
	
	ProjectGroup();

	virtual ~ProjectGroup();

	virtual ProjectIterator* createIIterator(std::string type);
};

#endif
