#include <exception>
#include <stack>
using namespace std;

#include "DepthFirstIterator.h"
#include "ProjectComponent.h"
#include "ProjectIterator.h"
#include "ProjectGroup.h"
#include "ProjectDecorator.h"

DepthFirstIterator::DepthFirstIterator(ProjectComponent* aRoot) : _root(aRoot) {
}

DepthFirstIterator::DepthFirstIterator() : _root(nullptr) {
}

// The stack holds borrowed pointers only, so there is nothing to free.
DepthFirstIterator::~DepthFirstIterator() {
}

void DepthFirstIterator::pushChildren(ProjectComponent* aNode) {
	ProjectGroup* group = dynamic_cast<ProjectGroup*>(aNode);
	if (group != nullptr) {
		// Reverse order so that _components[0] ends up on top of the stack.
		for (size_t i = group->components.size(); i > 0; --i) {
			if (group->components[i - 1] != nullptr) {
				_traversalStack.push(group->components[i - 1]);
			}
		}
		return;
	}

	ProjectDecorator* decorator = dynamic_cast<ProjectDecorator*>(aNode);
	if (decorator != nullptr && decorator->target != nullptr) {
		_traversalStack.push(decorator->target);
	}
	// A ProjectTask leaf has no children: nothing to push.
}

void DepthFirstIterator::first() {
	// Reset the stack (std::stack has no clear()).
	while (!_traversalStack.empty()) {
		_traversalStack.pop();
	}
	if (_root != nullptr) {
		_traversalStack.push(_root);
	}
}

void DepthFirstIterator::next() {
	if (_traversalStack.empty()) {
		return;
	}
	ProjectComponent* current = _traversalStack.top();
	_traversalStack.pop();
	pushChildren(current);
}

bool DepthFirstIterator::isDone() {
	return _traversalStack.empty();
}

ProjectComponent* DepthFirstIterator::currentItem() {
	if (_traversalStack.empty()) {
		return nullptr;
	}
	return _traversalStack.top();
}
