#include "Component.h"

#include <iostream>

static long GlobalID = 0;

Component::Component(const std::string& InComponentName)
    : id(GlobalID++),
      name(InComponentName + std::string("_") + std::to_string(id)) {
    std::cout << "Component `" << name << "` created!" << std::endl;
}

Component::~Component() {
    std::cout << "Component `" << name << "` destroyed!" << std::endl;
}
