#include <exception>
#include <stack>
using namespace std;

#ifndef __PriorityInspectionIterator_h__
#define __PriorityInspectionIterator_h__

#include "ProjectComponent.h"
#include "ProjectIterator.h"

class ProjectComponent;
// class ProjectIterator;
class PriorityInspectionIterator;

// Selective iterator: yields ONLY the ProjectTask leaves under _root that are
// currently in InspectionState, ordered by getCost() descending (the most
// expensive work stuck in inspection is the biggest site risk, so it comes
// first). Groups, decorators and tasks in other states are skipped.
//
// Snapshot policy: see first(). The qualifying tasks are captured once and
// held in _traversalStack (top = highest cost); next()/isDone()/currentItem()
// just walk that pre-computed sequence.
//
// Ownership: _root and every yielded task are borrowed, never deleted here.
class PriorityInspectionIterator: public ProjectIterator
{
	private: stack<ProjectComponent*> _traversalStack;
	private: ProjectComponent* _root;

	public: PriorityInspectionIterator(ProjectComponent* aRoot);

	PriorityInspectionIterator();

	public: virtual ~PriorityInspectionIterator();

	public: void first();

	public: void next();

	public: bool isDone();

	public: ProjectComponent* currentItem();
};

#endif
