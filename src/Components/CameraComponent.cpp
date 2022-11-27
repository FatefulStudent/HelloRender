#include "CameraComponent.h"

UCameraComponent::UCameraComponent()
    : UComponent(std::string("CameraComponent")) {
    ComponentClass = EComponentClass::UCameraComponent;
}
