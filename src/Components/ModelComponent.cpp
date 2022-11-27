#include "ModelComponent.h"

#include <utility>

UModelComponent::UModelComponent(std::string InPath)
    : UComponent(std::string("ModelComponent")), Path(std::move(InPath)) {
    ComponentClass = EComponentClass::UModelComponent;
}
