#include <exception>
using namespace std;

#ifndef __ProjectDecorator_h__
#define __ProjectDecorator_h__

#include "ProjectComponent.h"

// class ProjectComponent;
class ProjectDecorator;
class DepthFirstIterator;
class PriorityInspectionIterator;

class ProjectDecorator: public ProjectComponent
{
	protected: ProjectComponent* _target;

	// Iterators descend through a decorator into its wrapped target so that
	// decorated groups/tasks remain fully traversable.
	friend class DepthFirstIterator;
	friend class PriorityInspectionIterator;
	public: ProjectComponent* _unnamed_ProjectComponent_;

	public: ProjectDecorator(ProjectComponent* aT);

	public: void add(ProjectComponent* aX);

	public: void remove(ProjectComponent* aX);

	ProjectDecorator();
};

#endif
