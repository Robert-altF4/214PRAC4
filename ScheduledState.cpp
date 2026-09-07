#include <exception>
using namespace std;

#include "ScheduledState.h"
#include "ActiveState.h"
#include "ProjectTask.h"
#include "ProjectState.h"

void ScheduledState::startTask(ProjectTask* aTask) {
	transition(aTask, new ActiveState(), "ScheduledState", "ActiveState");
}

void ScheduledState::submitForInspection(ProjectTask* aTask) {
	invalidTransition(aTask, "submitForInspection", "ScheduledState");
}

void ScheduledState::completeTask(ProjectTask* aTask) {
	invalidTransition(aTask, "completeTask", "ScheduledState");
}

void ScheduledState::failInspection(ProjectTask* aTask) {
	invalidTransition(aTask, "failInspection", "ScheduledState");
}
