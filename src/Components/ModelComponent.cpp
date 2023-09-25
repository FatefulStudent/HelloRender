#include "ModelComponent.h"

#include <utility>

ModelComponent::ModelComponent(std::string inPath)
    : Component(std::string("ModelComponent")), path(std::move(inPath)) {
    componentClass = EComponentClass::modelComponent;
}
