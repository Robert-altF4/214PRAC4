#include <exception>
using namespace std;

#include "ActiveState.h"
#include "InspectionState.h"
#include "ProjectTask.h"
#include "ProjectState.h"

void ActiveState::startTask(ProjectTask* aTask) {
	invalidTransition(aTask, "startTask", "ActiveState");
}

void ActiveState::submitForInspection(ProjectTask* aTask) {
	transition(aTask, new InspectionState(), "ActiveState", "InspectionState");
}

void ActiveState::completeTask(ProjectTask* aTask) {
	invalidTransition(aTask, "completeTask", "ActiveState");
}

void ActiveState::failInspection(ProjectTask* aTask) {
	invalidTransition(aTask, "failInspection", "ActiveState");
}
