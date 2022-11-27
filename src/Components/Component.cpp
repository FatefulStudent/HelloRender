#include "Component.h"

#include <iostream>

static long GlobalID = 0;

UComponent::UComponent(const std::string& InComponentName)
    : ID(GlobalID++),
      Name(InComponentName + std::string("_") + std::to_string(ID)) {
    std::cout << "Component `" << Name << "` created!" << std::endl;
}

UComponent::~UComponent() {
    std::cout << "Component `" << Name << "` destroyed!" << std::endl;
}
