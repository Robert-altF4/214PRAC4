#include <exception>
using namespace std;

#include "CompletedState.h"
#include "ProjectTask.h"
#include "ProjectState.h"

// Terminal state: every operation is an invalid transition.

void CompletedState::startTask(ProjectTask* aTask) {
	invalidTransition(aTask, "startTask", "CompletedState");
}

void CompletedState::submitForInspection(ProjectTask* aTask) {
	invalidTransition(aTask, "submitForInspection", "CompletedState");
}

void CompletedState::completeTask(ProjectTask* aTask) {
	invalidTransition(aTask, "completeTask", "CompletedState");
}

void CompletedState::failInspection(ProjectTask* aTask) {
	invalidTransition(aTask, "failInspection", "CompletedState");
}
