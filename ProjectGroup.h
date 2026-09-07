#include <exception>
#include <vector>
using namespace std;

#ifndef __ProjectGroup_h__
#define __ProjectGroup_h__

#include "ProjectComponent.h"

// class ProjectComponent;
class ProjectGroup;
class DepthFirstIterator;
class PriorityInspectionIterator;

class ProjectGroup: public ProjectComponent
{
	private: vector<ProjectComponent*> _components;

	// The iterators are the only classes allowed to read _components directly;
	// client code must traverse via ProjectIterator (no public accessor).
	friend class DepthFirstIterator;
	friend class PriorityInspectionIterator;
	public: ProjectComponent* _unnamed_ProjectComponent_;

	public: int getCost();

	public: int getTime();

	public: void add(ProjectComponent* aX);

	public: void remove(ProjectComponent* aX);

	ProjectGroup();
};

#endif
