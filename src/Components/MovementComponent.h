#ifndef MOVEMENT_COMPONENT_H
#define MOVEMENT_COMPONENT_H

#include "Component.h"

#include <glm/vec3.hpp>

class UMovementComponent : public UComponent {
public:
    UMovementComponent(const glm::vec3& InVelocityDir, float InSpeed);
    virtual ~UMovementComponent() = default;

    glm::vec3 GetVelocityScaled() const;

    glm::vec3 VelocityDir = glm::vec3(0);
    float Speed = 0.0f;
};

#endif