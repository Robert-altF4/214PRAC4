#include "ProjectGroup.h"
#include "DepthFirstIterator.h"
#include "PriorityInspectionIterator.h"

ProjectGroup::ProjectGroup(){

}

int ProjectGroup::getCost(){
    int total = 0;
    for(ProjectComponent* i : this->components){
        if(i != nullptr){
            total += i->getCost();
        }

    }

    return total;

}

int ProjectGroup::getTime(){
    int total = 0;

    for(ProjectComponent* i : this->components){
        if(i != nullptr){
            total += i->getTime();
        }

    }

    return total;

}

void ProjectGroup::add(ProjectComponent* x){
    if(x != nullptr){
        this->components.push_back(x);
    }

}

void ProjectGroup::remove(ProjectComponent* x){
    bool exists = false;
    int index = 0;
    for(ProjectComponent* i : this->components){
        if((i != nullptr) && (i == x)){
            exists = true;
            break;

        }
        index++;
    }

    if(exists == true){
        this->components.erase(this->components.begin() + index);
    }
}

ProjectGroup::~ProjectGroup(){
    for(ProjectComponent* i : this->components){
        if(i != nullptr){
            delete i;
        }

    }

}

ProjectIterator* ProjectGroup::createIIterator(std::string type) {
    if (type == "depth") {
        return new DepthFirstIterator(this);
    } else if (type == "priority") {
        return new PriorityInspectionIterator(this);
    }
    return nullptr;
}


