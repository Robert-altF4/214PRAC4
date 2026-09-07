#include <exception>
using namespace std;

#ifndef __CompletedState_h__
#define __CompletedState_h__

// #include "ProjectTask.h"
#include "ProjectState.h"

class ProjectTask;
// class ProjectState;
class CompletedState;

class CompletedState: public ProjectState
{

	public: void startTask(ProjectTask* aTask);

	public: void submitForInspection(ProjectTask* aTask);

	public: void completeTask(ProjectTask* aTask);

	public: void failInspection(ProjectTask* aTask);
};

#endif
