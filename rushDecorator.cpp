#include "rushDecorator.h"

rushDecorator::rushDecorator(ProjectComponent* x) : ProjectDecorator(x){

}

int rushDecorator::getCost(){
    int cos = this->target->getCost();

    std::cout << "Due to a rush in construction the cost of the project has increased to account for overtime" << std::endl;
    return cos*10;
}

int rushDecorator::getTime(){
    int t = this->target->getTime();
    std::cout << "Due to a rush in construction the estimated time to complete the project has decreased" << std::endl;
    return t/2;

}

