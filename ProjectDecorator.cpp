#include "ProjectDecorator.h"

ProjectDecorator::ProjectDecorator(ProjectComponent* t){
    this->target = t;
}

ProjectDecorator::~ProjectDecorator(){
    if(this->target != nullptr){
        delete target;
    }
}