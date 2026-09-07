#include <exception>
#include <stack>
using namespace std;

#ifndef __DepthFirstIterator_h__
#define __DepthFirstIterator_h__

#include "ProjectComponent.h"
#include "ProjectIterator.h"

class ProjectComponent;
// class ProjectIterator;
class DepthFirstIterator;

// Pre-order depth-first traversal of the whole hierarchy under _root.
// Visits ProjectGroup nodes, ProjectTask leaves and decorators alike; a
// decorator is visited first and then its wrapped target (so the underlying
// task/group is still reachable through the decorator).
//
// Live-traversal policy: this iterator walks the live tree via the stack. It
// does NOT snapshot the structure, so adding/removing nodes while a traversal
// is in progress may skip or repeat nodes. Use it on a stable structure, or
// call first() again after restructuring.
//
// Ownership: _root and every visited node are borrowed, never deleted here.
class DepthFirstIterator: public ProjectIterator
{
	private: stack<ProjectComponent*> _traversalStack;
	private: ProjectComponent* _root;

	// Pushes the children of aNode (group children in reverse so the leftmost
	// child is on top; a decorator's wrapped target) onto _traversalStack.
	private: void pushChildren(ProjectComponent* aNode);

	public: DepthFirstIterator(ProjectComponent* aRoot);

	DepthFirstIterator();

	public: virtual ~DepthFirstIterator();

	public: void first();

	public: void next();

	public: bool isDone();

	public: ProjectComponent* currentItem();
};

#endif
