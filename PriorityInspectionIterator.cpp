#include <exception>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;

#include "PriorityInspectionIterator.h"
#include "ProjectComponent.h"
#include "ProjectIterator.h"
#include "ProjectTask.h"
#include "InspectionState.h"
#include "DepthFirstIterator.h"

PriorityInspectionIterator::PriorityInspectionIterator(ProjectComponent* aRoot) : _root(aRoot) {
}

PriorityInspectionIterator::PriorityInspectionIterator() : _root(nullptr) {
}

// The stack holds borrowed pointers only, so there is nothing to free.
PriorityInspectionIterator::~PriorityInspectionIterator() {
}

namespace {
	// Descending cost. Used with stable_sort so equal-cost tasks keep their
	// depth-first (document) order, which makes the output deterministic.
	bool costDescending(ProjectTask* aLeft, ProjectTask* aRight) {
		return aLeft->getCost() > aRight->getCost();
	}
}

void PriorityInspectionIterator::first() {
	// Snapshot policy: tasks and their qualification (InspectionState) are
	// captured once in first(). Later state/structure changes are not
	// reflected until a new iterator is created via createIIterator() (or
	// first() is called again). This avoids iterator invalidation if the tree
	// changes mid-traversal.
	while (!_traversalStack.empty()) {
		_traversalStack.pop();
	}

	// Reuse the depth-first walk to reach every node (decorated tasks are
	// reached because DepthFirstIterator descends into a decorator's target).
	vector<ProjectTask*> matches;
	DepthFirstIterator walk(_root);
	for (walk.first(); !walk.isDone(); walk.next()) {
		ProjectTask* task = dynamic_cast<ProjectTask*>(walk.currentItem());
		if (task != nullptr && dynamic_cast<InspectionState*>(task->getState()) != nullptr) {
			matches.push_back(task);
		}
	}

	stable_sort(matches.begin(), matches.end(), costDescending);

	// Push lowest cost first so the highest-cost task ends up on top.
	for (size_t i = matches.size(); i > 0; --i) {
		_traversalStack.push(matches[i - 1]);
	}
}

void PriorityInspectionIterator::next() {
	if (!_traversalStack.empty()) {
		_traversalStack.pop();
	}
}

bool PriorityInspectionIterator::isDone() {
	return _traversalStack.empty();
}

ProjectComponent* PriorityInspectionIterator::currentItem() {
	if (_traversalStack.empty()) {
		return nullptr;
	}
	return _traversalStack.top();
}
