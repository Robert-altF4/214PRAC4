#include <exception>
#include <string>
using namespace std;

#include "ProjectComponent.h"
#include "ProjectGroup.h"
#include "ProjectTask.h"
#include "ProjectDecorator.h"
#include "ProjectIterator.h"
#include "DepthFirstIterator.h"
#include "PriorityInspectionIterator.h"

void ProjectComponent::add(ProjectComponent* aX) {
	throw "Not yet implemented";
}

void ProjectComponent::remove(ProjectComponent* aX) {
	throw "Not yet implemented";
}

ProjectComponent::ProjectComponent() {
}

int ProjectComponent::getCost() {
	throw "Not yet implemented";
}

int ProjectComponent::getTime() {
	throw "Not yet implemented";
}

// Factory method for the Iterator pattern. Works for every node type
// (group, task or decorator) because both iterators accept any
// ProjectComponent* as their root; a leaf simply yields a one-item traversal.
// Ownership: the caller must delete the returned iterator. Returns nullptr
// (never throws) for an unrecognised type string.
ProjectIterator* ProjectComponent::createIIterator(string aType) {
	if (aType == "depth") {
		return new DepthFirstIterator(this);
	}
	if (aType == "priority") {
		return new PriorityInspectionIterator(this);
	}
	return nullptr;
}
