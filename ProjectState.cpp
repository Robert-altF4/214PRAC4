#include <exception>
#include <string>
#include <iostream>
using namespace std;

#include "ProjectState.h"
#include "ProjectTask.h"

ProjectState::~ProjectState() {
}

void ProjectState::invalidTransition(ProjectTask* aTask, const string& aAction, const string& aStateName) {
	cout << "[Invalid transition] Task(cost=" << (aTask != nullptr ? aTask->getCost() : 0)
	     << ") cannot " << aAction << " while in " << aStateName << ".\n";
}

void ProjectState::transition(ProjectTask* aTask, ProjectState* aNext, const string& aFrom, const string& aTo) {
	if (aTask == nullptr) {
		delete aNext;
		return;
	}
	cout << "[State] Task(cost=" << aTask->getCost() << "): " << aFrom << " -> " << aTo << "\n";
	// setState() deletes the state that is currently executing this method,
	// so nothing may touch `this` after this call.
	aTask->setState(aNext);
}
