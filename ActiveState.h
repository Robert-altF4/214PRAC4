#include <exception>
using namespace std;

#ifndef __ActiveState_h__
#define __ActiveState_h__

// #include "ProjectTask.h"
#include "ProjectState.h"

class ProjectTask;
// class ProjectState;
class ActiveState;

class ActiveState: public ProjectState
{

	public: void startTask(ProjectTask* aTask);

	public: void submitForInspection(ProjectTask* aTask);

	public: void completeTask(ProjectTask* aTask);

	public: void failInspection(ProjectTask* aTask);
};

#endif
