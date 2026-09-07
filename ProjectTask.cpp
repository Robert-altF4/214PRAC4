#include "ProjectTask.h"

ProjectTask::ProjectTask(int cost, int time){
    this->cost = cost;
    this->estTime = time;
    this->currState = nullptr;
}

void ProjectTask::add(ProjectComponent* x){};

void ProjectTask::remove(ProjectComponent* x){};

int ProjectTask::getCost(){
    return this->cost;
}

int ProjectTask::getTime(){
    return this->estTime;
}

void ProjectTask::setState(ProjectState* state){
    delete this->currState;
    this->currState = state;
}

void ProjectTask::startTask(ProjectTask* task){
    if(this->currState != nullptr){
    this->currState->startTask(task);
    }
}

void ProjectTask::submitForInspection(ProjectTask* task){
    if(this->currState != nullptr){
    this->currState->submitForInspection(task);
    }

}

void ProjectTask::completeTask(ProjectTask* task){
    if(this->currState != nullptr){
    this->currState->completeTask(task);
    }
}

void ProjectTask::failInspection(ProjectTask* task){
    if(this->currState){
    this->currState->failInspection(task);
    }
}

ProjectTask::~ProjectTask(){
    delete this->currState;
}