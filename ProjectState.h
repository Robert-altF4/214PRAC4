#include <exception>
#include <string>
using namespace std;

#ifndef __ProjectState_h__
#define __ProjectState_h__

// #include "ProjectTask.h"

class ProjectTask;
class ProjectState;

// Abstract State. State machine: Scheduled -> Active -> Inspection -> Completed,
// with failInspection looping Inspection -> Active. Every other call is an
// invalid transition: a safe no-op that prints a message and leaves the task
// unchanged.
//
// Ownership: a ProjectTask OWNS its current state (composition). Each valid
// transition allocates the next state with new and hands it to
// ProjectTask::setState(), which deletes the previous state. The task's
// destructor deletes the final state. States carry no per-instance data.
class ProjectState
{
	private: ProjectTask* _task;
	public: ProjectTask* _unnamed_ProjectTask_;
	public: ProjectTask* _unnamed_ProjectTask_2;

	public: virtual ~ProjectState();

	public: virtual void startTask(ProjectTask* aTask) = 0;

	public: virtual void submitForInspection(ProjectTask* aTask) = 0;

	public: virtual void completeTask(ProjectTask* aTask) = 0;

	public: virtual void failInspection(ProjectTask* aTask) = 0;

	// Shared helper so every concrete state prints an identical message:
	//   [Invalid transition] Task(cost=N) cannot <action> while in <State>.
	protected: void invalidTransition(ProjectTask* aTask, const string& aAction, const string& aStateName);

	// Shared helper for valid transitions: prints
	//   [State] Task(cost=N): <From> -> <To>
	// and installs aNext on the task (the task deletes the old state).
	protected: void transition(ProjectTask* aTask, ProjectState* aNext, const string& aFrom, const string& aTo);
};

#endif
