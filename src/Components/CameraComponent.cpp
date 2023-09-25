#include "CameraComponent.h"

CameraComponent::CameraComponent()
    : Component(std::string("CameraComponent")) {
    componentClass = EComponentClass::cameraComponent;
}
