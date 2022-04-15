#include "Component.h"

#include <iostream>

UComponent::UComponent() {
    static long GlobalID = 0;
    ID = GlobalID++;

    std::cout << "Component #" << ID << " created!" << std::endl;
}

UComponent::UComponent(long&& NewID) : 
    ID(NewID) 
{
    std::cout << "Component #" << ID << " created!" << std::endl;
}

UComponent::~UComponent() {
    std::cout << "Component #" << ID << " destroyed!" << std::endl;
}
