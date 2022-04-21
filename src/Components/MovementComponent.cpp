#include "MovementComponent.h"

#include "glm/glm.hpp"

UMovementComponent::UMovementComponent(const glm::vec3& InVelocityDir, float InSpeed)
    : VelocityDir(glm::normalize(InVelocityDir)), Speed(InSpeed) {
    ComponentClass = EComponentClass::UMovementComponent;
}

glm::vec3 UMovementComponent::GetVelocityScaled() const {
    return VelocityDir * Speed;
}
