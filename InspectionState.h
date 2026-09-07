#include <exception>
using namespace std;

#ifndef __InspectionState_h__
#define __InspectionState_h__

// #include "ProjectTask.h"
#include "ProjectState.h"

class ProjectTask;
// class ProjectState;
class InspectionState;

class InspectionState: public ProjectState
{

	public: void startTask(ProjectTask* aTask);

	public: void submitForInspection(ProjectTask* aTask);

	public: void completeTask(ProjectTask* aTask);

	public: void failInspection(ProjectTask* aTask);
};

#endif
