#include <exception>
using namespace std;

#ifndef __ProjectTask_h__
#define __ProjectTask_h__

// #include "ProjectState.h"
#include "ProjectComponent.h"

class ProjectState;
// class ProjectComponent;
class ProjectTask;

class ProjectTask: public ProjectComponent
{
	private: int _cost;
	private: int _estTime;
	private: ProjectState* _currState;
	public: ProjectState* _unnamed_ProjectState_;
	public: ProjectComponent* _unnamed_ProjectComponent_;
	public: ProjectState* _unnamed_ProjectState_2;

	public: ProjectTask(int aCost, int aTime);

	// Owns _currState (composition): deletes it.
	public: virtual ~ProjectTask();

	public: void add(ProjectComponent* aX);

	public: void remove(ProjectComponent* aX);

	public: int getCost();

	public: int getTime();

	ProjectTask();

	// Takes ownership of aState and deletes the previous state.
	public: void setState(ProjectState* aState);

	// NOTE (added by the Iterator/State side): read-only accessor so that
	// PriorityInspectionIterator can test whether a task is in InspectionState
	// without reaching into private data. Nothing else exposed the state type.
	// The task keeps ownership of the returned pointer; do not delete it.
	public: ProjectState* getState() const;

	public: void startTask(ProjectTask* aTask);

	public: void submitForInspection(ProjectTask* aTask);

	public: void completeTask(ProjectTask* aTask);

	public: void failInspection(ProjectTask* aTask);
};

#endif
