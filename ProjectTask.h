#ifndef PROJECTTASK_H
#define PROJECTTASK_H

#include "ProjectComponent.h"
#include "ProjectState.h"

class ProjectTask : public ProjectComponent {

private:
	int cost;
	int estTime;
	ProjectState* currState;

public:
	ProjectTask(int cost, int time);

	virtual void add(ProjectComponent* x);

	virtual void remove(ProjectComponent* x);

	virtual int getCost();

	virtual int getTime();

	void setState(ProjectState* state);

	void startTask(ProjectTask* task);

	void submitForInspection(ProjectTask* task);

	void completeTask(ProjectTask* task);

	void failInspection(ProjectTask* task);

	virtual ~ProjectTask();
};

#endif
