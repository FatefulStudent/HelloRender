#include "Component.h"

UComponent::UComponent() {
    static long GlobalID = 0;
    ID = GlobalID++;
}

UComponent::UComponent(long&& NewID) : 
    ID(NewID) 
{
}


