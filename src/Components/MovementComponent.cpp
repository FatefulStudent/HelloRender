#include "MovementComponent.h"

#include "glm/glm.hpp"

MovementComponent::MovementComponent(const glm::vec3& inVelocityDir,
                                       float inSpeed)
    : Component(std::string("MovementComponent")),
      velocityDir(glm::normalize(inVelocityDir)),
      speed(inSpeed) {
    componentClass = EComponentClass::movementComponent;
}

glm::vec3 MovementComponent::GetVelocityScaled() const {
    return velocityDir * speed;
}
