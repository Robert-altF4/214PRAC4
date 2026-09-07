#include <exception>
#include <string>
using namespace std;

#ifndef __ProjectComponent_h__
#define __ProjectComponent_h__

// #include "ProjectGroup.h"
// #include "ProjectTask.h"
// #include "ProjectDecorator.h"
// #include "ProjectIterator.h"

// Forward declarations are required for the association members below to
// compile (they were commented out by the code generator).
class ProjectGroup;
class ProjectTask;
class ProjectDecorator;
class ProjectIterator;
class ProjectComponent;

class ProjectComponent
{
	public: ProjectGroup* _unnamed_ProjectGroup_;
	public: ProjectTask* _unnamed_ProjectTask_;
	public: ProjectDecorator* _unnamed_ProjectDecorator_;

	// Base of a polymorphic hierarchy (Composite / Decorator / Iterator all
	// treat nodes through ProjectComponent*), so the destructor and the
	// operations overridden by subclasses must be virtual.
	public: virtual ~ProjectComponent() {}

	public: virtual void add(ProjectComponent* aX);

	public: virtual void remove(ProjectComponent* aX);

	ProjectComponent();

	public: virtual int getCost();

	public: virtual int getTime();

	// Iterator factory. Recognised types: "depth" (full pre-order traversal)
	// and "priority" (InspectionState tasks, highest cost first). Any other
	// string returns nullptr. The CALLER OWNS the returned iterator and must
	// delete it; the iterator itself never owns or deletes tree nodes.
	public: ProjectIterator* createIIterator(string aType);
};

#endif
