#include "ProjectDecorator.h"
#include "DepthFirstIterator.h"
#include "PriorityInspectionIterator.h"

ProjectDecorator::ProjectDecorator(ProjectComponent* t){
    this->target = t;
}

ProjectDecorator::~ProjectDecorator(){
    if(this->target != nullptr){
        delete target;
    }
}

ProjectIterator* ProjectDecorator::createIIterator(std::string type) {
    if (type == "depth") {
        return new DepthFirstIterator(this);
    } else if (type == "priority") {
        return new PriorityInspectionIterator(this);
    }
    return nullptr;
}