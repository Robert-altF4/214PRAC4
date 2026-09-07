#include <exception>
using namespace std;

#include "ProjectTask.h"
#include "ProjectState.h"
#include "ScheduledState.h"
#include "ProjectComponent.h"

// Every task starts life in ScheduledState.
ProjectTask::ProjectTask(int aCost, int aTime)
	: _cost(aCost), _estTime(aTime), _currState(new ScheduledState()) {
}

ProjectTask::~ProjectTask() {
	delete _currState;
	_currState = nullptr;
}

void ProjectTask::add(ProjectComponent* aX) {
	throw "Not yet implemented";
}

void ProjectTask::remove(ProjectComponent* aX) {
	throw "Not yet implemented";
}

int ProjectTask::getCost() {
	return this->_cost;
}

int ProjectTask::getTime() {
	throw "Not yet implemented";
}

ProjectTask::ProjectTask()
	: _cost(0), _estTime(0), _currState(new ScheduledState()) {
}

// Ownership: the task owns its state. Installing a new state deletes the old
// one. Safe to call from inside the old state's own method because the caller
// does not touch its members afterwards (see ProjectState::transition).
void ProjectTask::setState(ProjectState* aState) {
	if (aState == _currState) {
		return;
	}
	delete _currState;
	_currState = aState;
}

ProjectState* ProjectTask::getState() const {
	return _currState;
}

// The State pattern delegation. The generated signature carries a ProjectTask*
// parameter; the state always acts on THIS task, so the parameter is unused.

void ProjectTask::startTask(ProjectTask* aTask) {
	(void)aTask;
	_currState->startTask(this);
}

void ProjectTask::submitForInspection(ProjectTask* aTask) {
	(void)aTask;
	_currState->submitForInspection(this);
}

void ProjectTask::completeTask(ProjectTask* aTask) {
	(void)aTask;
	_currState->completeTask(this);
}

void ProjectTask::failInspection(ProjectTask* aTask) {
	(void)aTask;
	_currState->failInspection(this);
}
