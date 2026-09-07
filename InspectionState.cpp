#include <exception>
using namespace std;

#include "InspectionState.h"
#include "ActiveState.h"
#include "CompletedState.h"
#include "ProjectTask.h"
#include "ProjectState.h"

void InspectionState::startTask(ProjectTask* aTask) {
	invalidTransition(aTask, "startTask", "InspectionState");
}

void InspectionState::submitForInspection(ProjectTask* aTask) {
	invalidTransition(aTask, "submitForInspection", "InspectionState");
}

void InspectionState::completeTask(ProjectTask* aTask) {
	transition(aTask, new CompletedState(), "InspectionState", "CompletedState");
}

// Rework: the inspection failed, so the task goes back to being worked on.
void InspectionState::failInspection(ProjectTask* aTask) {
	transition(aTask, new ActiveState(), "InspectionState", "ActiveState");
}
