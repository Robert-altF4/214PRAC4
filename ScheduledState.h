#include <exception>
using namespace std;

#ifndef __ScheduledState_h__
#define __ScheduledState_h__

// #include "ProjectTask.h"
#include "ProjectState.h"

class ProjectTask;
// class ProjectState;
class ScheduledState;

class ScheduledState: public ProjectState
{

	public: void startTask(ProjectTask* aTask);

	public: void submitForInspection(ProjectTask* aTask);

	public: void completeTask(ProjectTask* aTask);

	public: void failInspection(ProjectTask* aTask);
};

#endif
