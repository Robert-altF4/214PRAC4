#include "hazardDecorator.h"

hazardDecorator::hazardDecorator(ProjectComponent* x, std::string w):ProjectDecorator(x){
    this->warning = w;
}

int hazardDecorator::getCost(){
    int c = this->target->getCost();

    std::cout << "Because of the " << this->warning << " warning the cost to complete the project will increase to pay contractors to clean it up" << std::endl;
    return c*15;
}

int hazardDecorator::getTime(){
    int t = this->target->getTime();

    std::cout << "Because of the " << this->warning << " warning the time to complete the project will increase to as we wait for the hazard to be cleaned up" << std::endl;

    return t*5;


}